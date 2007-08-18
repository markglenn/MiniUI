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
			return start + ( end - start ) / currentDuration * duration;			
		}
		
		///////////////////////////////////////////////////////////////////////
		Animate::Animate ( luabind::object *object, std::string attribute, 
						   std::string animation, double end, double duration )
		///////////////////////////////////////////////////////////////////////
		{
			_pObject = object;
			_attribute = attribute;
			_end = end;
			
			// TODO: Starting point and animation function
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
			
			double value = _pFunc ( _start, _end, _duration, duration );
			
			// TODO: Set the new value
			
			return true;
		}
		
		///////////////////////////////////////////////////////////////////////
		Animate::AnimateFunc* Animate::GetAnimation ( std::string animation )
		///////////////////////////////////////////////////////////////////////
		{
			return LinearAnimation;
		}
	}
}
