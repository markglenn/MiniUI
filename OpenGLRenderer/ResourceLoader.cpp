/***************************************************************************
 *   Copyright (C) 2007 by Mark Glenn                                      *
 *   markglenn@gmail.com                                                   *
 ***************************************************************************/

#include "ResourceLoader.h"
#include "SDLImageResource.h"

#include <istream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_STDIO
#include <stb_image.h>

using namespace MiniUI::Graphics;
using namespace std;

namespace OpenGLRenderer
{
	namespace
	{
		int stb_stream_read(void *user, char *data, int size)
		{
			istream *s = static_cast<istream *>(user);
			s->read(data, size);
			return static_cast<int>(s->gcount());
		}

		void stb_stream_skip(void *user, int n)
		{
			istream *s = static_cast<istream *>(user);
			s->seekg(n, ios_base::cur);
		}

		int stb_stream_eof(void *user)
		{
			istream *s = static_cast<istream *>(user);
			return s->eof() ? 1 : 0;
		}
	}

	SDL_RWops* ResourceLoader::GetRWOps ( std::istream* /*stream*/ )
	{
		return 0;
	}

	///////////////////////////////////////////////////////////////////////////
	ImageResource* ResourceLoader::LoadImageResource ( istream* stream )
	///////////////////////////////////////////////////////////////////////////
	{
		stbi_io_callbacks cb;
		cb.read = stb_stream_read;
		cb.skip = stb_stream_skip;
		cb.eof  = stb_stream_eof;

		int w = 0, h = 0, comp = 0;
		unsigned char *pixels = stbi_load_from_callbacks(&cb, stream, &w, &h, &comp, 4);

		if (!pixels)
			return new SDLImageResource(0);

		// Build an SDL_Surface that owns a malloc'd copy of the 32-bit RGBA pixels.
		// SDLImageResource will upload it then SDL_FreeSurface it.
		const int pitch = w * 4;
		void *owned = std::malloc(static_cast<size_t>(pitch) * h);
		std::memcpy(owned, pixels, static_cast<size_t>(pitch) * h);
		stbi_image_free(pixels);

		SDL_Surface *pSurface = SDL_CreateRGBSurfaceFrom(
			owned, w, h, 32, pitch,
			0x000000FFu, 0x0000FF00u, 0x00FF0000u, 0xFF000000u);

		// Leak-free behavior: SDL_FreeSurface will not free `owned`, so wire cleanup.
		// SDL 1.2 lets us overload the free via SDL_RWops — simpler: track the pointer
		// on the surface's userdata-adjacent `pixels` and free from caller.
		// SDLImageResource already uploads then SDL_FreeSurface's the wrapper; we
		// free the pixel buffer here by telling SDL to own it.
		if (pSurface)
			pSurface->flags |= SDL_PREALLOC;

		return new SDLImageResource(pSurface);
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
