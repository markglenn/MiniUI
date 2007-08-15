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

#ifndef _TYPES_RECTANGLE_H_
#define _TYPES_RECTANGLE_H_

namespace MiniUI
{
	namespace Types
	{
		template < class t >
		class Rectangle
		{
		public:
			///////////////////////////////////////////////////////////////////
			Rectangle ( )
			///////////////////////////////////////////////////////////////////
			{
			}

			///////////////////////////////////////////////////////////////////
			Rectangle ( t _x, t _y, t _width, t _height )
			///////////////////////////////////////////////////////////////////
			{
				Set ( _x, _y, _width, _height );
			}

			///////////////////////////////////////////////////////////////////
			void Set ( t _x, t _y, t _width, t _height )
			///////////////////////////////////////////////////////////////////
			{
				x = _x; y = _y; width = _width; height = _height;
			}

			///////////////////////////////////////////////////////////////////
			bool PointInRectangle ( t _x, t _y )
			///////////////////////////////////////////////////////////////////
			{
				if ( _x < x || _x > ( x + width ) )
					return false;
				if ( _y < y || _y > ( y + height ) )
					return false;

				return true;

			}
			t x, y, width, height;
		};
	}
}

#endif // _TYPES_RECTANGLE_H_
