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

#include "SDLImageResource.h"

namespace OpenGLRenderer
{
	///////////////////////////////////////////////////////////////////////////
	SDLImageResource::SDLImageResource ( SDL_Surface *pSurface )
	///////////////////////////////////////////////////////////////////////////
	{
		_texture = ConvertToTexture ( pSurface );
	}

	///////////////////////////////////////////////////////////////////////////
	SDLImageResource::~SDLImageResource ( )
	///////////////////////////////////////////////////////////////////////////
	{

	}

	///////////////////////////////////////////////////////////////////////////
	GLuint SDLImageResource::ConvertToTexture ( SDL_Surface *pSurface )
	///////////////////////////////////////////////////////////////////////////
	{
		GLuint texture;

		if ( pSurface == NULL )
			return 0;

		// Have OpenGL generate a texture object handle for us
		glGenTextures( 1, &texture );

		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, texture );

		// Set the texture's stretching properties
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		// Edit the texture object's image data using the information SDL_Surface gives us
		if ( pSurface->format->BitsPerPixel == 24 && pSurface->format->Rshift == 16 )
			glTexImage2D( GL_TEXTURE_2D, 0, 3, pSurface->w, pSurface->h, 0,
				  GL_BGR, GL_UNSIGNED_BYTE, pSurface->pixels );
		else if ( pSurface->format->BitsPerPixel == 24 && pSurface->format->Rshift == 0 )
			glTexImage2D( GL_TEXTURE_2D, 0, 3, pSurface->w, pSurface->h, 0,
				  GL_RGB, GL_UNSIGNED_BYTE, pSurface->pixels );		
		else if ( pSurface->format->BitsPerPixel == 32 )
			glTexImage2D( GL_TEXTURE_2D, 0, 4, pSurface->w, pSurface->h, 0,
				  GL_RGBA, GL_UNSIGNED_BYTE, pSurface->pixels );

		_width = pSurface->w;
		_height = pSurface->h;
		_bpp = pSurface->format->BitsPerPixel;


		SDL_FreeSurface( pSurface );

		return texture;
	}
}
