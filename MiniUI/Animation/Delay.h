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
 
#ifndef _MINIUI_ANIMATION_DELAY_
#define _MINIUI_ANIMATION_DELAY_

#include "Animatable.h"
#include <luabind/object.hpp>
#include <MiniUI/LuaSystem/LuaVirtualMachine.h>

namespace MiniUI
{
	namespace Animation
	{
		class Delay : public Animatable
		{
		public:
			
			Delay ( double duration );
			virtual ~Delay ( );
			
			bool Run ( double duration );
						
			static void RegisterWithLua ( LuaSystem::LuaVirtualMachine* );
		
		private:
			double				_duration;			
			double				_currentDuration;
		};
	}
}

#endif // _MINIUI_ANIMATION_DELAY_
