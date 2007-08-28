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

#include "Delay.h" 
#include <luabind/luabind.hpp>
#include <luabind/adopt_policy.hpp>

using namespace luabind;
using namespace MiniUI::LuaSystem;

namespace MiniUI
{
	namespace Animation
	{		
		///////////////////////////////////////////////////////////////////////
		Delay::Delay ( double duration )
		///////////////////////////////////////////////////////////////////////
		{
			_currentDuration = 0.0;
			_duration = duration;
		}
		
		///////////////////////////////////////////////////////////////////////
		Delay::~Delay ( )
		///////////////////////////////////////////////////////////////////////
		{
			
		}
		
		///////////////////////////////////////////////////////////////////////
		bool Delay::Run ( double duration )
		///////////////////////////////////////////////////////////////////////
		{
			// No more animation
			if ( _currentDuration >= _duration )
				return RunChildren ( duration );

			_currentDuration += duration;
			
			// Past the duration?
			if ( _currentDuration > _duration )
				return RunChildren ( _currentDuration - _duration );
			
			return true;
		}
		
		///////////////////////////////////////////////////////////////////////
		void Delay::RegisterWithLua ( LuaSystem::LuaVirtualMachine* pVM )
		///////////////////////////////////////////////////////////////////////
		{
			module(*pVM)
			[
				class_<Delay,Animatable>("Delay")
				.def(constructor<double>())
				.def("Run", &Delay::Run)
				.def("Stop", &Animatable::Stop)
				.def("Add", &Animatable::Add, adopt(_2))
			];

		}

	}
}
