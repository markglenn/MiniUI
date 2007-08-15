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

#ifndef _MINIUI_UISYSTEM_WIDGET_H_
#define _MINIUI_UISYSTEM_WIDGET_H_

#include "../Graphics/Renderable.h"
#include <string>
#include <luabind/luabind.hpp>
#include <MiniUI/TinyXPath/tinyxml.h>
#include <MiniUI/LuaSystem/LuaVirtualMachine.h>
#include "EventArea.h"
#include "../Input/Mouse.h"

namespace MiniUI
{
	namespace UISystem
	{
		class Widget;

		typedef std::vector< Widget* > WidgetList;
		struct WidgetChildArea
		{
			Types::Rectangle<int> 	area;
			WidgetList 				children;
			int 					depth;
		};

		typedef std::vector<WidgetChildArea> WidgetChildren;

		class Widget
		{
		public:

			Widget ( );
			virtual ~Widget ( );

			static void RegisterWithLua ( LuaSystem::LuaVirtualMachine* );

			void SetRenderable ( Graphics::Renderable* pRenderable );

			void AddWidgetChildArea ( WidgetChildArea childArea )
				{ _widgetChildren.push_back ( childArea ); }
			WidgetChildren* GetWidgetChildren ( ) { return &_widgetChildren; }

			void AddEventArea ( EventArea* eventArea )
				{ _eventAreas.push_back ( eventArea ); }

			Graphics::Renderable* GetRenderable ( ) { return _pRenderable; }

			void SetName ( std::string name ) { _name = name; }
			std::string Name ( ) { return _name; }

			void HandleMouseInput ( Input::Mouse *pMouse );

			// Lua methods //
			virtual void Update ( int timestep ) { };

			Graphics::GraphicalRect* GetGraphicalRect ( std::string id );
			void UpdateRenderable ( ) { _pRenderable->OnChanged(); }

			void SetAngle ( float angle );
			float GetAngle ( ) const;

			void SetPositionX ( int x ) { _pRenderable->position.x = x; }
			void SetPositionY ( int y ) { _pRenderable->position.y = y; }
			int GetPositionX ( ) const { return _pRenderable->position.x; }
			int GetPositionY ( ) const { return _pRenderable->position.y; }

			float GetOpacity ( ) const { return _pRenderable->opacity; }
			void SetOpacity ( float o ) { _pRenderable->opacity = o; }

			int GetWidth ( ) const { return _pRenderable->centerPosition.x * 2; }
			int GetHeight ( ) const { return _pRenderable->centerPosition.y * 2; }

			virtual void OnLoad ( TinyXPath::TiXmlElement *pSkin, TinyXPath::TiXmlElement *pLayout ) {}
			virtual void OnLayout ( ) { }

			int GetChildWidgetCount ( int area );
			Widget* GetChildWidget ( int area, int widget );

			void Destroy ( );

			Types::Vector2D<int>* GetPosition ( ) const;

		private:
			Graphics::Renderable 	*_pRenderable;
			WidgetChildren			_widgetChildren;
			EventAreaList			_eventAreas;
			std::string				_name;
		};

		class Widget_wrapper : public Widget, public luabind::wrap_base
		{
		public:
			Widget_wrapper()
				: Widget()
			{}

			virtual void Update( int timestep )
			{
				call<void>("Update", timestep);
			}

			static void default_Update ( Widget* ptr, int timestep )
			{
				return ptr->Widget::Update( timestep );
			}

			virtual void OnLoad ( TinyXPath::TiXmlElement *pSkin, TinyXPath::TiXmlElement *pLayout )
			{
				call<void>("OnLoad", pSkin, pLayout);
			}

			static void default_OnLoad ( Widget* ptr, TinyXPath::TiXmlElement *pSkin, TinyXPath::TiXmlElement *pLayout )
			{
				return ptr->Widget::OnLoad ( pSkin, pLayout );
			}

			virtual void OnLayout ( )
			{
				call<void>( "OnLayout" );
			}

			static void default_OnLayout ( Widget* ptr )
			{
				return ptr->Widget::OnLayout ( );
			}
		};
	}
}

#endif // _MINIUI_UISYSTEM_WIDGET_H_
