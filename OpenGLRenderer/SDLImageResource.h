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

#ifndef _SDLIMAGERESOURCE_H_
#define _SDLIMAGERESOURCE_H_

#include <MiniUI/Graphics/ImageResource.h>
#include <SDL/SDL.h>
#include <GL/gl.h>

namespace OpenGLRenderer
{
	class SDLImageResource : public MiniUI::Graphics::ImageResource
	{
	public:
		SDLImageResource ( SDL_Surface *pSurface );
		virtual ~SDLImageResource ( );

		virtual unsigned int Width () 	{ return _width; }
		virtual unsigned int Height () 	{ return _height; }
		virtual unsigned int BPP () 	{ return _bpp; }

		GLuint GetTexture () { return _texture; }

		virtual std::string id () { return ""; }



	private:
		GLuint ConvertToTexture ( SDL_Surface *pSurface );

		GLuint _texture;

		unsigned int _width;
		unsigned int _height;
		unsigned int _bpp;
	};
}

#endif // _SDLIMAGERESOURCE_H_
