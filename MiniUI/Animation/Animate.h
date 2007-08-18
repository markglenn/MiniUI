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
 
#ifndef _MINIUI_ANIMATION_ANIMATOR_
#define _MINIUI_ANIMATION_ANIMATOR_

#include "Animatable.h"
#include <luabind/object.hpp>

namespace MiniUI
{
	namespace Animation
	{
		class Animate : public Animatable
		{
		public:
			
			Animate ( luabind::object *object, std::string attribute, 
					  std::string animation, double end, double duration );
			virtual ~Animate ( );
			
			virtual bool Run ( double duration );
		
		private:
			typedef double AnimateFunc(double start, double end, double duration, double currentDuration);
			
			AnimateFunc* GetAnimation ( std::string animation );
			
			luabind::object*	_pObject;
			std::string			_attribute;
			double				_start;
			double				_end;
			double				_duration;
			
			AnimateFunc* 		_pFunc;
		};
	}
}

#endif // _MINIUI_ANIMATION_ANIMATOR_
