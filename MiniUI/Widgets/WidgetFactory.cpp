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

#include "WidgetFactory.h"
#include <MiniUI/LuaSystem/LuaVirtualMachine.h>
#include <luabind/luabind.hpp>
#include <luabind/adopt_policy.hpp>

using namespace MiniUI::LuaSystem;
using namespace luabind;

namespace MiniUI
{
	namespace Widgets
	{
		WidgetFactory::RegistryMap WidgetFactory::_registry;
		
		///////////////////////////////////////////////////////////////////////
		WidgetFactory::WidgetFactory ( )
		///////////////////////////////////////////////////////////////////////
		{
			
		}
		
		///////////////////////////////////////////////////////////////////////
		WidgetFactory::~WidgetFactory ( )
		///////////////////////////////////////////////////////////////////////
		{
			
		}
		
		///////////////////////////////////////////////////////////////////////
		Widget* WidgetFactory::Create ( std::string id )
		///////////////////////////////////////////////////////////////////////
		{
			RegistryMap::const_iterator regEntry = _registry.find ( id );
			LuaVirtualMachine *pVM = LuaVirtualMachine::Instance( );
			
			//printf ("Creating widget: %s\n", id.c_str() );
			if (regEntry != _registry.end()) 
				return regEntry->second();
			
			if ( type (globals(*pVM)[ id.c_str() ]) != LUA_TNIL )
				return call_function<Widget*>(*pVM, id.c_str())[ adopt(result) ];
			
			return new Widget ( );

		}
		
		///////////////////////////////////////////////////////////////////////
		void WidgetFactory::Register ( std::string id, BaseCreateFn function )
		///////////////////////////////////////////////////////////////////////
		{
			_registry[id] = function;
		}
	}
}
