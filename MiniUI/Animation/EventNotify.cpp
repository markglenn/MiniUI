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

#include "EventNotify.h" 
#include <luabind/luabind.hpp>
#include <luabind/adopt_policy.hpp>

using namespace luabind;
using namespace MiniUI::LuaSystem;
using namespace MiniUI::Widgets;

namespace MiniUI
{
	namespace Animation
	{		
		///////////////////////////////////////////////////////////////////////
		EventNotify::EventNotify ( Widget *pWidget )
		///////////////////////////////////////////////////////////////////////
		{
			_notified = false;
			_pWidget = pWidget;
		}
		
		///////////////////////////////////////////////////////////////////////
		EventNotify::~EventNotify ( )
		///////////////////////////////////////////////////////////////////////
		{
			
		}
		
		///////////////////////////////////////////////////////////////////////
		bool EventNotify::Run ( double duration )
		///////////////////////////////////////////////////////////////////////
		{
			// No more animation
			if ( !_notified )
			{
				_notified = true;
				_pWidget->Call ( "OnEventNotify", luabind::object() );	
			}

			return RunChildren ( duration );
		}
		
		///////////////////////////////////////////////////////////////////////
		void EventNotify::RegisterWithLua ( LuaSystem::LuaVirtualMachine* pVM )
		///////////////////////////////////////////////////////////////////////
		{
			module(*pVM)
			[
				class_<EventNotify,Animatable>("EventNotify")
				.def(constructor<Widget *>())
				.def("Run", &EventNotify::Run)
				.def("Stop", &Animatable::Stop)
				.def("Add", &Animatable::Add, adopt(_2))
			];

		}

	}
}
