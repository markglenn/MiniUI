/***************************************************************************
 *   Copyright (C) 2007 by Mark Glenn                                      *
 *   markglenn@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "UIManager.h"
#include "Host/HostIntegration.h"
#include "TinyXPath/xpath_processor.h"
#include "Host/IRenderer.h"

#include <luabind/luabind.hpp>
#include <boost/test/utils/foreach.hpp>

#include <iostream>

using namespace MiniUI::Host;
using namespace MiniUI::TinyXPath;
using namespace MiniUI::UISystem;
using namespace MiniUI::Widgets;
using namespace luabind;
using namespace std;

namespace MiniUI
{
	IMemory* HostIntegration::Memory = 0;
	IResourceLoader* HostIntegration::ResourceLoader = 0;
	IRenderer* HostIntegration::Renderer = 0;

	///////////////////////////////////////////////////////////////////////////
	UIManager::UIManager ( )
	///////////////////////////////////////////////////////////////////////////
	{
	}

	///////////////////////////////////////////////////////////////////////////
	UIManager::~UIManager()
	///////////////////////////////////////////////////////////////////////////
	{
		ScreenMap::iterator i;
		for ( i = _screens.begin(); i != _screens.end(); i++ )
			delete i->second;
	}

	///////////////////////////////////////////////////////////////////////////
	bool UIManager::Initialize ( )
	///////////////////////////////////////////////////////////////////////////
	{

		if ( !_luaVM.Running() )
		{
			printf( "Could not initialize lua\n" );
			return false;
		}

		_luaVM.LoadLibs ( );

		Register ( );
		return true;
	}

	///////////////////////////////////////////////////////////////////////////
	bool UIManager::LoadUIArchive ( IArchive *pArchive )
	///////////////////////////////////////////////////////////////////////////
	{
		if ( pArchive == NULL )
			return false;

		// Set the texture manager's archive for this skin
		_textureManager.SetArchive ( pArchive );
		_luaVM.LoadScript ( "skin.lua", pArchive );

		return _skin.LoadSkinFile ( pArchive );
	}

	///////////////////////////////////////////////////////////////////////////
	bool UIManager::LoadScreens ( string rootXML, IArchive *pArchive )
	///////////////////////////////////////////////////////////////////////////
	{
		if ( pArchive == NULL )
			return false;

		istream *pStream = pArchive->LoadFile ( rootXML );

		// File wasn't loaded properly
		if ( !pStream )
			return false;

		string xmlData;

		// Read the entire document
		while ( !pStream->eof() )
		{
			string xmlLine;
			getline ( *pStream, xmlLine );

			xmlData += xmlLine + "\n";
		}

		// Document is loaded, finally parse it
		TiXmlDocument document;
		document.Parse ( xmlData.c_str() );

		// We no longer need the open file
		delete pStream;

		// Loop through and load each screen
		xpath_processor xpath ( document.RootElement(), "/interface/screen" );
		int xpathsize = xpath.u_compute_xpath_node_set();
		for ( int i = 0; i < xpathsize; i++ )
		{
			Screen *pScreen = new Screen ( );

			// If the screen loads properly, build it
			if ( pScreen->LoadScreen ( (TiXmlElement *)xpath.XNp_get_xpath_node ( i ) ) )
			{
				_screens[ pScreen->id() ] = pScreen;
				_pCurrentScreen = pScreen;
				pScreen->BuildScreen ( &_skin );
			}
			else
				delete pScreen;
		}

		return true;
	}

	///////////////////////////////////////////////////////////////////////////
	bool UIManager::Update ( unsigned int timestep, Input::Mouse* pMouse )
	///////////////////////////////////////////////////////////////////////////
	{
		// Send the update to the widgets
		WidgetList* pList = _pCurrentScreen->GetWidgetList ( );
		UpdateWidget ( pList, timestep, pMouse );

		HostIntegration::Renderer->Update ( _pCurrentScreen, pMouse );

		return true;
	}

	///////////////////////////////////////////////////////////////////////////
	void UIManager::UpdateWidget ( WidgetList* pWidgetList, int timestep, Input::Mouse* pMouse  )
	///////////////////////////////////////////////////////////////////////////
	{
		for ( WidgetList::iterator i = pWidgetList->begin(); i != pWidgetList->end(); i++ )
		{
			(*i)->Update ( timestep );

			WidgetChildren::iterator j;
			WidgetChildren *pWidgetChildren = (*i)->GetWidgetChildren();
			for ( j = pWidgetChildren->begin(); j != pWidgetChildren->end(); j++ )
				UpdateWidget ( &(*j).children, timestep, pMouse );
		}
	}

	///////////////////////////////////////////////////////////////////////////
	bool UIManager::InitializeScripts ( )
	///////////////////////////////////////////////////////////////////////////
	{
		for ( ScreenMap::iterator i = _screens.begin(); i != _screens.end(); i++ )
			WidgetList* pWidgetList = (*i).second->GetWidgetList();
	}
	
	///////////////////////////////////////////////////////////////////////////
	Widget* FindWidget ( std::string id )
	///////////////////////////////////////////////////////////////////////////
	{
		return UIManager::Instance()->GetCurrentScreen()->FindWidget( id );
	}
	
	///////////////////////////////////////////////////////////////////////////
	void UIManager::Register ( )
	///////////////////////////////////////////////////////////////////////////
	{	
		module(&(*_luaVM), "MiniUI")
		[
			def("FindWidget", &FindWidget)
		];

	}
	
	///////////////////////////////////////////////////////////////////////////
	void UIManager::FireEvent ( Widgets::Widget *pWidget, std::string event,
							  luabind::object const& o )
	///////////////////////////////////////////////////////////////////////////
	{
		OnUIEvent.event = event;
		OnUIEvent.pWidget = pWidget;
		OnUIEvent.parameter = (object *)&o;
		
		OnUIEvent ( );
	}


}
