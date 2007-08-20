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
 
#include "Animatable.h"
#include "Animate.h"

#include <luabind/luabind.hpp>

using namespace luabind;
namespace MiniUI
{
	namespace Animation
	{
		///////////////////////////////////////////////////////////////////////
		Animatable::Animatable ( )
		///////////////////////////////////////////////////////////////////////
		{
			
		}
		
		///////////////////////////////////////////////////////////////////////
		Animatable::~Animatable ( )
		///////////////////////////////////////////////////////////////////////
		{
			// Make sure we clean out the animation list
			Stop ( );
		}
		
		///////////////////////////////////////////////////////////////////////
		void Animatable::Stop ( )
		///////////////////////////////////////////////////////////////////////
		{
			AnimatableList::iterator i;
			for ( i = _animations.begin(); i != _animations.end(); i++ )
			{
				// Stop each child
				(*i)->Stop ( );
				
				// Remove the animation from the list
				delete (*i);
			}
			
			// Clear out the dead pointers
			_animations.clear ( );
		}
		
		///////////////////////////////////////////////////////////////////////
		bool Animatable::RunChildren ( double duration )
		///////////////////////////////////////////////////////////////////////
		{
			AnimatableList::iterator i;
			AnimatableList _deleteList;
			
			for ( i = _animations.begin(); i != _animations.end(); )
			{
				if ( !(*i)->Run ( duration ) )
				{		
					delete (*i);
					
					// Need to remove this from the animation from the list
					i = _animations.erase ( i );
				}
				else i++;
			}
			
			return !_animations.empty();
		}
	}
}
