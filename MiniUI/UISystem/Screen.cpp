//
// C++ Implementation: Screen
//
// Description:
//
//
// Author: Mark Glenn <markglenn@gmail.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "Screen.h"
#include "Widget.h"
#include "Skin.h"

#include "../TinyXPath/xpath_static.h"

#include "../Host/HostIntegration.h"
#include "../Host/IRenderer.h"
#include "../Graphics/TextureManager.h"
#include "../Types/Vector2D.h"
#include "../Types/Integer.h"
#include "../LuaSystem/LuaVirtualMachine.h"
#include <luabind/luabind.hpp>
#include <luabind/adopt_policy.hpp>

using namespace MiniUI::TinyXPath;
using namespace MiniUI::Graphics;
using namespace MiniUI::Host;
using namespace MiniUI::Types;
using namespace MiniUI::LuaSystem;

using namespace luabind;

namespace MiniUI
{

	namespace UISystem
	{
		///////////////////////////////////////////////////////////////////////
		Screen::Screen()
		///////////////////////////////////////////////////////////////////////
		{
		}

		///////////////////////////////////////////////////////////////////////
		Screen::~Screen()
		///////////////////////////////////////////////////////////////////////
		{
			WidgetList::iterator i;
			for ( i = _widgetList.begin(); i != _widgetList.end(); i++ )
				delete (*i);
		}

		///////////////////////////////////////////////////////////////////////
		bool Screen::LoadScreen ( TiXmlElement *pElement )
		///////////////////////////////////////////////////////////////////////
		{
			_id = std::string(pElement->Attribute("id"));
			_pElement = pElement;

			return true;
		}

		///////////////////////////////////////////////////////////////////////
		bool Screen::BuildScreen ( Skin* pSkin )
		///////////////////////////////////////////////////////////////////////
		{
			TiXmlElement *pChild = _pElement->FirstChildElement();

			// Loop through all the widgets
			while ( pChild != NULL )
			{
				_widgetList.push_back ( LoadWidget ( pChild, pSkin ) );
				pChild = pChild->NextSiblingElement();
			}

			OnLayout ( &_widgetList );

			return true;
		}

		///////////////////////////////////////////////////////////////////////
		void Screen::OnLayout ( WidgetList *pWidgetList )
		///////////////////////////////////////////////////////////////////////
		{
			WidgetList::iterator i;
			for ( i = pWidgetList->begin(); i != pWidgetList->end(); i++ )
			{
				(*i)->OnLayout ( );

				WidgetChildren::iterator j;
				for ( j = (*i)->GetWidgetChildren()->begin(); j != (*i)->GetWidgetChildren()->end(); j++ )
					OnLayout ( &( (*j).children ) );
			}
		}

		///////////////////////////////////////////////////////////////////////
		Widget* Screen::LoadWidget ( TiXmlElement* pChild, Skin* pSkin, int depth )
		///////////////////////////////////////////////////////////////////////
		{
			// Find the widget
			TiXmlElement *pWidgetElement = pSkin->GetWidgetElement( pChild->ValueStr() );
			LuaVirtualMachine *pVM = LuaVirtualMachine::Instance( );

			Widget *pWidget;
			
			if ( type (globals(*pVM)[ pChild->ValueStr() ]) == LUA_TNIL )
				pWidget = new Widget ( );
			else
				pWidget = call_function<Widget*>(*pVM, pChild->ValueStr().c_str())[ adopt(result) ];

			pWidget->SetName ( pChild->ValueStr() );

			Renderable *pRenderable = HostIntegration::Renderer->CreateRenderable ( );
			pWidget->SetRenderable ( pRenderable );

			// Skinned widget
			if ( pWidgetElement )
			{
				// Load the image attached to this widget
				if ( pWidgetElement->Attribute ("src") )
					pRenderable->image = TextureManager::Instance()->LoadImage
							( pWidgetElement->Attribute ( "src" ) );

				// Set the center position
				if ( pWidgetElement->Attribute ("width") )
					pRenderable->centerPosition.x =
							( i_xpath_int ( pChild, pWidgetElement->Attribute ("width") ) / 2 );

				if ( pWidgetElement->Attribute ("height") )
					pRenderable->centerPosition.y =
							( i_xpath_int ( pChild, pWidgetElement->Attribute ("height") ) / 2 );
				
				// Load the angle
				double angle = 0.f;
				if ( pWidgetElement->Attribute ("angle") )
					o_xpath_double ( pChild, pWidgetElement->Attribute ("angle"), angle );
			
				pRenderable->angle = angle;
				
			}

			pRenderable->position.x = 0;
			pRenderable->position.y = 0;
			
			// Load the position
			o_xpath_int ( pChild, "@x", pRenderable->position.x );
			o_xpath_int ( pChild, "@y", pRenderable->position.y );
			
			if ( pWidgetElement )
			{
				LoadLayout ( pRenderable, pChild, pWidgetElement );
				LoadChildren ( pWidget, pChild, pWidgetElement, pSkin, depth );
				LoadEventAreas ( pWidget, pChild, pWidgetElement );
			}		
			
			pWidget->OnLoad ( pWidgetElement, pChild );
						
	
			pRenderable->OnChanged();

			return pWidget;
		}

		///////////////////////////////////////////////////////////////////////
		bool Screen::LoadLayout ( Renderable* pRenderable,
								  TiXmlElement* pChild, TiXmlElement* pWidget )
		///////////////////////////////////////////////////////////////////////
		{
			// Find the layout objects
			xpath_processor xpath ( pWidget, "/widget/layout/section" );

			// Loop through all the sections
			int numSections = xpath.u_compute_xpath_node_set ( );
			for ( int i = 0; i < numSections; i++ )
			{
				GraphicalRect rect;
				TiXmlElement* pSection = (TiXmlElement*)xpath.XNp_get_xpath_node ( i );
				TiXmlElement* pSource = pSection->FirstChildElement ( "source" );
				TiXmlElement* pDestination = pSection->FirstChildElement ( "destination" );

				rect.id = pSection->Attribute ( "id" );

				// Calculate the final destination rectangle;
				Rectangle<int> destRectangle;
				destRectangle.x = i_xpath_int ( pChild, pDestination->Attribute ("x") );
				destRectangle.y = i_xpath_int ( pChild, pDestination->Attribute ("y") );
				destRectangle.width = i_xpath_int ( pChild, pDestination->Attribute ("width") );
				destRectangle.height = i_xpath_int ( pChild, pDestination->Attribute ("height") );

				// Calculate the final source rectangle;
				Rectangle<int> sourceRectangle;
				sourceRectangle.x = i_xpath_int ( pChild, pSource->Attribute ("x") );
				sourceRectangle.y = i_xpath_int ( pChild, pSource->Attribute ("y") );
				sourceRectangle.width = i_xpath_int ( pChild, pSource->Attribute ("width") );
				sourceRectangle.height = i_xpath_int ( pChild, pSource->Attribute ("height") );

				// Build the polygon
				rect.coordinates[0].position.x = destRectangle.x;
				rect.coordinates[0].position.y = destRectangle.y;
				rect.coordinates[0].texture.x = (double)sourceRectangle.x;
				rect.coordinates[0].texture.y = (double)sourceRectangle.y;

				rect.coordinates[1].position.x = destRectangle.x;
				rect.coordinates[1].position.y = destRectangle.y + destRectangle.height;
				rect.coordinates[1].texture.x = (double)sourceRectangle.x;
				rect.coordinates[1].texture.y = (double)sourceRectangle.y + (double)sourceRectangle.height;

				rect.coordinates[2].position.x = destRectangle.x + destRectangle.width;
				rect.coordinates[2].position.y = destRectangle.y + destRectangle.height;
				rect.coordinates[2].texture.x = (double)sourceRectangle.x + (double)sourceRectangle.width;
				rect.coordinates[2].texture.y = (double)sourceRectangle.y + (double)sourceRectangle.height;

				rect.coordinates[3].position.x = destRectangle.x + destRectangle.width;
				rect.coordinates[3].position.y = destRectangle.y;
				rect.coordinates[3].texture.x = (double)sourceRectangle.x + (double)sourceRectangle.width;
				rect.coordinates[3].texture.y = (double)sourceRectangle.y;

				// Convert the texture coordinates into percentage of the texture
				for ( int j = 0; j < 4; j++ )
				{
					rect.coordinates[j].texture.x /= pRenderable->image->Width();
					rect.coordinates[j].texture.y /= pRenderable->image->Height();
				}

				rect.isVisible = true;

				// Visibility
				if ( pSection->Attribute ( "visibility" ) )
				{
					if ( strcmp ( pSection->Attribute ( "visibility" ), "hidden" ) == 0 )
						rect.isVisible = false;
				}
				pRenderable->push_back ( rect );

			}

			return true;
		}

		///////////////////////////////////////////////////////////////////////
		bool Screen::LoadChildren ( Widget* pWidget, TiXmlElement* pChild,
				TiXmlElement* pWidgetEl, Skin* pSkin, int depth )
		///////////////////////////////////////////////////////////////////////
		{
			// Find the layout objects
			xpath_processor xpath ( pWidgetEl, "/widget/children/area" );

			bool foundChildren = false;
			// Loop through all the child areas
			int numChildAreas = xpath.u_compute_xpath_node_set ( );
			for ( int i = 0; i < numChildAreas; i++ )
			{
				TiXmlElement* pChildArea = (TiXmlElement*)xpath.XNp_get_xpath_node ( i );

				WidgetChildArea widgetChildArea;
				widgetChildArea.depth = depth;

				// Set the child area
				if ( pChildArea->Attribute("x") )
					o_xpath_int ( pChild, pChildArea->Attribute("x"), widgetChildArea.area.x );
				if ( pChildArea->Attribute("y") )
					o_xpath_int ( pChild, pChildArea->Attribute("y"), widgetChildArea.area.y );
				if ( pChildArea->Attribute("width") )
					o_xpath_int ( pChild, pChildArea->Attribute("width"), widgetChildArea.area.width );
				if ( pChildArea->Attribute("height") )
					o_xpath_int ( pChild, pChildArea->Attribute("height"), widgetChildArea.area.height );

				// Do the selection of the children
				if ( pChildArea->Attribute ( "select" ) )
				{
					xpath_processor childxpath ( pChild, pChildArea->Attribute ( "select" ) );

					int numChildren = childxpath.u_compute_xpath_node_set ( );
					for ( int j = 0; j < numChildren; j++ )
					{
						Widget* pChildWidget = LoadWidget ( (TiXmlElement*)childxpath.XNp_get_xpath_node ( j ),
								pSkin, depth + 1 );
						widgetChildArea.children.push_back ( pChildWidget );
						foundChildren = true;
					}

				}

				// Push the child area back
				if ( foundChildren )
					pWidget->AddWidgetChildArea( widgetChildArea );
			}

			return true;
		}

		///////////////////////////////////////////////////////////////////////
		bool Screen::LoadEventAreas ( Widget* pWidget,
					TiXmlElement* pChild, TiXmlElement* pWidgetEl )
		///////////////////////////////////////////////////////////////////////
		{
			// Find the layout objects
			xpath_processor xpath ( pWidgetEl, "/widget/events/areas/area" );
			LuaVirtualMachine *pVM = LuaVirtualMachine::Instance( );

			// Loop through all the event areas
			int numAreas = xpath.u_compute_xpath_node_set ( );
			for ( int i = 0; i < numAreas; i++ )
			{
				TiXmlElement* pEventArea = (TiXmlElement*)xpath.XNp_get_xpath_node ( i );

				EventArea *pArea = NULL;
				try
				{
					std::string areaName = pWidget->Name() + "_" + pEventArea->Attribute ( "id" );
					pArea = call_function<EventArea*>(*pVM, areaName.c_str() )[ adopt(result) ];
				}
				catch ( luabind::error ) { continue; }

				// Set the event area
				pArea->area.x = i_xpath_int ( pChild, pEventArea->Attribute ("x") );
				pArea->area.y = i_xpath_int ( pChild, pEventArea->Attribute ("y") );
				pArea->area.width = i_xpath_int ( pChild, pEventArea->Attribute ("width") );
				pArea->area.height = i_xpath_int ( pChild, pEventArea->Attribute ("height") );

				pArea->id = pEventArea->Attribute ( "id" );

				pWidget->AddEventArea ( pArea );
				pArea->widget = pWidget;
			}

			return true;

		}
	}

}
