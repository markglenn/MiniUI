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

#include "Widget.h"

#include <string>

#include "../Types/Integer.h"
#include "../Types/Float.h"
#include "../TinyXPath/xpath_static.h"
#include "../Host/HostIntegration.h"
#include "../Host/IResourceLoader.h"
#include "../Host/IRenderer.h"
#include "../LuaSystem/LuaVirtualMachine.h"
#include <luabind/adopt_policy.hpp>

#include "TextArea.h"

#include <Lua/lua.h>
#include <luabind/luabind.hpp>

using namespace std;
using namespace MiniUI::TinyXPath;
using namespace MiniUI::Types;
using namespace MiniUI::Graphics;
using namespace MiniUI::Host;
using namespace MiniUI::LuaSystem;
using namespace luabind;

namespace MiniUI
{
	namespace UISystem
	{

		///////////////////////////////////////////////////////////////////////
		Widget::Widget ( )
		///////////////////////////////////////////////////////////////////////
		{
		}

		///////////////////////////////////////////////////////////////////////
		Widget::~Widget ( )
		///////////////////////////////////////////////////////////////////////
		{
			EventAreaList::iterator i;
			for ( i = _eventAreas.begin(); i != _eventAreas.end(); i++ )
				delete *i;
		}

		///////////////////////////////////////////////////////////////////////
		void Widget::SetRenderable ( Graphics::Renderable* pRenderable )
		///////////////////////////////////////////////////////////////////////
		{
			_pRenderable = pRenderable;
		}

		///////////////////////////////////////////////////////////////////////
		void Widget::HandleMouseInput ( Input::Mouse *pMouse )
		///////////////////////////////////////////////////////////////////////
		{
			Vector2D<int> position;
			position = _pRenderable->GetTranslatedPosition ( pMouse->x, pMouse->y );

			EventAreaList::iterator i;
			for ( i = _eventAreas.begin(); i != _eventAreas.end(); i++ )
				(*i)->HandleMouse ( position.x, position.y, pMouse );
		}

		///////////////////////////////////////////////////////////////////////
		void Widget::SetAngle ( float angle )
		///////////////////////////////////////////////////////////////////////
		{
			_pRenderable->angle = angle;
		}

		///////////////////////////////////////////////////////////////////////
		float Widget::GetAngle ( ) const
		///////////////////////////////////////////////////////////////////////
		{
			return _pRenderable->angle;
		}

		///////////////////////////////////////////////////////////////////////
		int Widget::GetChildWidgetCount ( int area )
		///////////////////////////////////////////////////////////////////////
		{
			return _widgetChildren[area].children.size();
		}

		///////////////////////////////////////////////////////////////////////
		Widget* Widget::GetChildWidget ( int area, int widget )
		///////////////////////////////////////////////////////////////////////
		{
			return _widgetChildren[area].children[widget];
		}

		///////////////////////////////////////////////////////////////////////
		void Widget::Destroy ( )
		///////////////////////////////////////////////////////////////////////
		{

		}

		///////////////////////////////////////////////////////////////////////
		GraphicalRect* Widget::GetGraphicalRect ( std::string id )
		///////////////////////////////////////////////////////////////////////
		{
			std::vector<Graphics::GraphicalRect>::iterator i;
			for ( i = _pRenderable->begin(); i != _pRenderable->end(); i++ )
				if ( (*i).id == id )
					return &(*i);

			return NULL;
		}

		///////////////////////////////////////////////////////////////////////
		void Widget::RegisterWithLua ( LuaSystem::LuaVirtualMachine* pVM )
		///////////////////////////////////////////////////////////////////////
		{
			module(*pVM)
			[
				class_<Widget, Widget_wrapper>("Widget")
				.def(constructor<>(), adopt(result))
				.def("Update", &Widget::Update, &Widget_wrapper::default_Update)
				.def("OnLoad", &Widget::OnLoad, &Widget_wrapper::default_OnLoad)
				.def("OnLayout", &Widget::OnLayout, &Widget_wrapper::default_OnLayout)
				.property("angle", &Widget::GetAngle, &Widget::SetAngle)
				.property("x", &Widget::GetPositionX, &Widget::SetPositionX)
				.property("y", &Widget::GetPositionY, &Widget::SetPositionY)
				.property("width", &Widget::GetWidth)
				.property("height", &Widget::GetHeight)
				.property("opacity", &Widget::GetOpacity, &Widget::SetOpacity)
				.def("GetChildWidgetCount", &Widget::GetChildWidgetCount)
				.def("GetChildWidget", &Widget::GetChildWidget)
				.def("GetGraphicalRect", &Widget::GetGraphicalRect)
				.def("UpdateRenderable", &Widget::UpdateRenderable)
			];

			module(*pVM)
			[
				class_<GraphicalRect>("GraphicalRect")
				.def_readonly("id", &GraphicalRect::id)
				.def_readwrite("isVisible", &GraphicalRect::isVisible)
			];
			
			module(*pVM)
			[
				class_<TextArea, Widget>("TextArea")
				.def(constructor<>(), adopt(result))

			];
		}

	}
}
