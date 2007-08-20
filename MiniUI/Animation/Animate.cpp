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

#include "Animate.h" 
#include <luabind/luabind.hpp>

#include <math.h>

using namespace luabind;
using namespace MiniUI::LuaSystem;

namespace MiniUI
{
	namespace Animation
	{
		// Animation functions
		///////////////////////////////////////////////////////////////////////
		double LinearAnimation ( double start, double end, double duration, 
								 double currentDuration )
		///////////////////////////////////////////////////////////////////////
		{
			return start + ( end - start ) / duration * currentDuration;			
		}
		
		double sineInOut ( double start, double end, double duration, 
						   double currentDuration )
		{ 
			return -(end - start) / 2.0 * ( cos ( 3.1415926535898 * currentDuration / duration) - 1) + start; 
		}
		
		///////////////////////////////////////////////////////////////////////
		Animate::Animate ( luabind::object object, std::string attribute, 
						   std::string animation, double end, double duration )
		///////////////////////////////////////////////////////////////////////
		{
			_object = object;
			_attribute = attribute;
			_end = end;
			_currentDuration = 0.0;
			_duration = duration;
			
			// Set the start point from the object itself
			_start = object_cast<double>(_object[_attribute]);
			
			_pFunc = this->GetAnimation( animation );
		}
		
		///////////////////////////////////////////////////////////////////////
		Animate::~Animate ( )
		///////////////////////////////////////////////////////////////////////
		{
			
		}
		
		///////////////////////////////////////////////////////////////////////
		bool Animate::Run ( double duration )
		///////////////////////////////////////////////////////////////////////
		{
			// No more animation
			if ( _pFunc == NULL )
				return RunChildren ( duration );
			
			_currentDuration += duration;
			
			// Past the duration?
			if ( _currentDuration > _duration )
			{
				_object[_attribute] = _pFunc ( _start, _end, _duration, _duration );
				_pFunc = NULL;
				
				return RunChildren ( _currentDuration - _duration );
			}
			
			// Set the value
			_object[_attribute] = _pFunc ( _start, _end, _duration, _currentDuration );
			
			return true;
		}
		
		///////////////////////////////////////////////////////////////////////
		void Animate::Stop ( )
		///////////////////////////////////////////////////////////////////////
		{
			Animatable::Stop ( );
			_pFunc = NULL;
		}
		
		///////////////////////////////////////////////////////////////////////
		Animate::AnimateFunc* Animate::GetAnimation ( std::string animation )
		///////////////////////////////////////////////////////////////////////
		{
			if ( animation == "sineInOut" )
				return sineInOut;
			
			return LinearAnimation;
		}
		
		///////////////////////////////////////////////////////////////////////
		void Animate::RegisterWithLua ( LuaSystem::LuaVirtualMachine* pVM )
		///////////////////////////////////////////////////////////////////////
		{
			module(*pVM)
			[
				class_<Animate>("Animate")
				.def(constructor<luabind::object, std::string, std::string, double, double>())
				.def("Run", &Animate::Run)
				.def("Stop", &Animatable::Stop)
			];

		}
	}
}
