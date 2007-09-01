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

#ifndef _MINIUI_GRAPHICS_RENDERABLE_H_
#define _MINIUI_GRAPHICS_RENDERABLE_H_

#include <vector>
#include <list>
#include "../Types/Vector2D.h"
#include "../Types/Rectangle.h"
#include "ImageResource.h"

namespace MiniUI
{
	namespace Graphics
	{
		struct Coordinate
		{
			Types::Vector2D<unsigned int> 	position;
			Types::Vector2D<double>			texture;
		};

		struct GraphicalRect
		{
			GraphicalRect ( ) {}
			GraphicalRect ( const GraphicalRect& rect )
			{
				coordinates[0] = rect.coordinates[0];
				coordinates[1] = rect.coordinates[1];
				coordinates[2] = rect.coordinates[2];
				coordinates[3] = rect.coordinates[3];

				id = rect.id;
				isVisible = rect.isVisible;
			}

			std::string		id;
			bool			isVisible;
			Coordinate 		coordinates[4];
		};

		class Renderable;

		typedef std::vector<GraphicalRect>::iterator GraphicalRectIterator;
		typedef std::list < Renderable *> RenderableList;

		class Renderable : public std::vector<GraphicalRect>
		{
		public:
			Renderable ( ) { }
			virtual ~Renderable ( ) { }

			float 					angle;
			Types::Vector2D<double>	scale;
			Types::Vector2D<int>	position;
			Types::Vector2D<int> 	size;
			ImageResource* 			image;
			float					opacity;

			virtual void OnChanged ( ) { }
			virtual Types::Vector2D<int> GetTranslatedPosition ( int x, int y ) = 0;

		};

	}
}

#endif // _MINIUI_GRAPHICS_RENDERABLE_H_
