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

#include "ResourceLoader.h"
#include "SDLImageResource.h"

#include <istream>

#include <SDL/SDL_image.h>

using namespace MiniUI::Graphics;
using namespace std;


namespace OpenGLRenderer
{
	///////////////////////////////////////////////////////////////////////////
	static int _stream_seek(SDL_RWops *context, int offset, int whence)
	///////////////////////////////////////////////////////////////////////////
	{
		if ( whence == SEEK_SET )
			((istream *)context->hidden.unknown.data1)->seekg(offset, ios_base::beg );
		else if ( whence == SEEK_CUR )
			((istream *)context->hidden.unknown.data1)->seekg(offset, ios_base::cur );
		else
			((istream *)context->hidden.unknown.data1)->seekg(offset, ios_base::end );
		return ((istream *)context->hidden.unknown.data1)->tellg();
	}

	///////////////////////////////////////////////////////////////////////////
	static int _stream_read(SDL_RWops *context, void *ptr, int size, int maxnum)
	///////////////////////////////////////////////////////////////////////////
	{
		((istream *)context->hidden.unknown.data1)->read ((char *)ptr, size * maxnum);

		return maxnum;
	}

	///////////////////////////////////////////////////////////////////////////
	static int _stream_write(SDL_RWops *context, const void *ptr, int size, int num)
	///////////////////////////////////////////////////////////////////////////
	{
		return 0; /* ignored */
	}

	///////////////////////////////////////////////////////////////////////////
	static int _stream_close(SDL_RWops *context)
	///////////////////////////////////////////////////////////////////////////
	{
		if (! context)
			return 0; /* may be SDL_RWclose is called by atexit */


		delete ((istream *)context->hidden.unknown.data1);
		SDL_FreeRW (context);
		return 0;
	}

	///////////////////////////////////////////////////////////////////////////
	SDL_RWops* ResourceLoader::GetRWOps ( std::istream* stream )
	///////////////////////////////////////////////////////////////////////////
	{
		register SDL_RWops* rwops;

		rwops = SDL_AllocRW ();

		if (! rwops)
			return 0;

		rwops->hidden.unknown.data1 = stream;
		rwops->read = _stream_read;
		rwops->write = _stream_write;
		rwops->seek = _stream_seek;
		rwops->close = _stream_close;

		return rwops;
	}

	///////////////////////////////////////////////////////////////////////////
	ImageResource* ResourceLoader::LoadImageResource ( istream* stream )
	///////////////////////////////////////////////////////////////////////////
	{
		SDL_RWops* pOps = GetRWOps(stream);
		SDL_Surface* pSurface = IMG_Load_RW ( pOps, 0 );

		SDL_FreeRW ( pOps );
		return new SDLImageResource ( pSurface );
	}

	///////////////////////////////////////////////////////////////////////////
	ImageResource* ResourceLoader::LoadImageResourceFromRaw ( char *data,
			int x, int y, int bpp)
	///////////////////////////////////////////////////////////////////////////
	{
		SDL_Surface* pSurface;

		if ( bpp == 32 )
			pSurface = SDL_CreateRGBSurfaceFrom  ( data, x, y, bpp,
					x * bpp / 8, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000 );
		else
			pSurface = SDL_CreateRGBSurfaceFrom  ( data, x, y, bpp,
				x * bpp / 8, 0x00FF0000, 0x0000FF00, 0x000000FF, 0 );

		return new SDLImageResource ( pSurface );
	}
}
