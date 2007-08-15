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

#include "TextureManager.h"
#include "../Host/IResourceLoader.h"

using namespace MiniUI::Host;
using namespace std;

namespace MiniUI
{
	namespace Graphics
	{
		///////////////////////////////////////////////////////////////////////
		TextureManager::TextureManager ( )
		///////////////////////////////////////////////////////////////////////
		{
			_pArchive = NULL;
		}

		///////////////////////////////////////////////////////////////////////
		TextureManager::~TextureManager ( )
		///////////////////////////////////////////////////////////////////////
		{
			// Remove all images
			ImageResourceMap::iterator i;
			for ( i = _imageMap.begin(); i != _imageMap.end(); i++ )
				delete i->second;
		}

		///////////////////////////////////////////////////////////////////////
		ImageResource* TextureManager::LoadImage ( std::string path )
		///////////////////////////////////////////////////////////////////////
		{
			ImageResourceMap::iterator i = _imageMap.find ( path );

			// An image already exists
			if ( i != _imageMap.end () )
				return i->second;

			// Load up the image
			IResourceLoader* pResourceLoader = HostIntegration::ResourceLoader;

			istream* pStream = _pArchive->LoadFile ( path );

			// Image doesn't exist
			if ( pStream == NULL )
			{
				printf ("Image not found: %s\n", path.c_str());
				return NULL;
			}

			// Load the image
			ImageResource *pImage = pResourceLoader->LoadImageResource ( pStream );

			// We no longer need the stream
			delete pStream;

			// Store the image in map
			_imageMap [ path ] = pImage;

			return pImage;
		}
	}

}
