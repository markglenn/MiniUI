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

#ifndef _MINIUI_HOST_IRESOURCELOADER_H_
#define _MINIUI_HOST_IRESOURCELOADER_H_

#include "../Graphics/ImageResource.h"

namespace MiniUI
{
	namespace Host
	{
		class IResourceLoader
		{
		public:
			virtual Graphics::ImageResource* LoadImageResource ( std::istream* stream ) = 0;
			virtual Graphics::ImageResource* LoadImageResourceFromRaw
					( char *data, int x, int y, int bpp) = 0;
		};
	}
}

#endif // _MINIUI_HOST_IRESOURCELOADER_H_
