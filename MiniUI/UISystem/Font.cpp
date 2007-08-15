//
// C++ Implementation: Font
//
// Description:
//
//
// Author: Mark Glenn <markglenn@gmail.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "Font.h"
#include "../Host/HostIntegration.h"
#include "../Graphics/ImageResource.h"
#include "../Host/IResourceLoader.h"
#include "../Host/IRenderer.h"

using namespace std;

using namespace MiniUI::Host;
using namespace MiniUI::Graphics;
using namespace MiniUI::TinyXPath;

namespace MiniUI
{

	namespace UISystem
	{
		Font::FontListType Font::FontList;
		
		///////////////////////////////////////////////////////////////////////
		Font::Font ( ) :
				_pImage ( 0 )
		///////////////////////////////////////////////////////////////////////
		{
		}

		///////////////////////////////////////////////////////////////////////
		Font::~Font()
		///////////////////////////////////////////////////////////////////////
		{
			delete ( _pImage );
		}

		///////////////////////////////////////////////////////////////////////
		bool Font::LoadFont ( TiXmlElement* pElement, IArchive *pArchive )
		///////////////////////////////////////////////////////////////////////
		{
			// File exists?
			if ( pElement == NULL )
				return false;

			boost::shared_ptr<Font> pFont( new Font ( ) );
			
			pFont->SetName ( pElement->Attribute("id") );
			pFont->LoadImage ( pElement->Attribute("src"), pArchive );

			FontList[pFont->Name()] = pFont;
			return true;
		}

		///////////////////////////////////////////////////////////////////////
		Font* Font::GetFont ( std::string name ) 
		///////////////////////////////////////////////////////////////////////
		{
			FontListType::iterator i = FontList.find(name);
			
			if ( i == FontList.end() )
				return NULL;
			
			return boost::get_pointer<Font> ( i->second );
		}

		///////////////////////////////////////////////////////////////////////
		void Font::SetImageResource ( ImageResource* pImage )
		///////////////////////////////////////////////////////////////////////
		{
			_pImage = pImage;
			ConvertToCharacters ( );
		}
		
		///////////////////////////////////////////////////////////////////////
		ImageResource* Font::LoadImage ( string path, IArchive* pArchive )
		///////////////////////////////////////////////////////////////////////
		{
			IResourceLoader* pResourceLoader = HostIntegration::ResourceLoader;

			istream* pStream = pArchive->LoadFile ( path );

			// Image doesn't exist
			if ( pStream == NULL )
			{
				printf ("Image not found: %s\n", path.c_str());
				return NULL;
			}

			unsigned short id;
			pStream->read ( (char *)&id, 2 );
			pStream->read ( (char *)&_header, sizeof(FontHeader) );

			if ( id != 0xF2BF )
			{
				delete pStream;
				return NULL;
			}

			pStream->seekg ( -2, ios_base::cur );
			// Grab char widths
			pStream->read ( _widths, 256 );

			char *imageData = new char [ _header.x * _header.y * _header.bpp / 8 ];

			pStream->read ( imageData, _header.x * _header.y * _header.bpp / 8 );

			ImageResource *pImage = pResourceLoader->LoadImageResourceFromRaw ( imageData,
						_header.x, _header.y, _header.bpp );

			delete[] imageData;

			delete pStream;

			SetImageResource ( pImage );
		}

		///////////////////////////////////////////////////////////////////////
		void Font::ConvertToCharacters ( )
		///////////////////////////////////////////////////////////////////////
		{
			int numCharsX = _header.x / _header.cellX;
			int numCharsY = _header.y / _header.cellY;

			int numChars = numCharsX * numCharsY;

			// Go through each character
			for ( int i = 0; i < 256; i++ )
			{

				// Setup the locations
				if ( _header.base > i || _header.base + numChars <= i )
					_characters[i].isVisible = false;

				else
				{
					_characters[i].isVisible = true;

					_characters[i].coordinates[0].position.x = 0;
					_characters[i].coordinates[0].position.y = 0;
					_characters[i].coordinates[0].texture.x = ( (i - _header.base) % numCharsX ) * _header.cellX;
					_characters[i].coordinates[0].texture.y = ( (i - _header.base) / numCharsX ) * _header.cellY;

					_characters[i].coordinates[1] = _characters[i].coordinates[0];
					_characters[i].coordinates[2] = _characters[i].coordinates[0];
					_characters[i].coordinates[3] = _characters[i].coordinates[0];

					_characters[i].coordinates[1].position.y = _header.cellY;
					_characters[i].coordinates[1].texture.y += _header.cellY;

					_characters[i].coordinates[2].position.x = _widths[i];
					_characters[i].coordinates[2].position.y = _header.cellY;
					_characters[i].coordinates[2].texture.x	+= _widths[i];
					_characters[i].coordinates[2].texture.y += _header.cellY;

					_characters[i].coordinates[3].position.x = _widths[i];
					_characters[i].coordinates[3].texture.x += _widths[i];

					for ( int j = 0; j < 4; j++ )
					{
						_characters[i].coordinates[j].texture.x /=  (float)_pImage->Width();
						_characters[i].coordinates[j].texture.y /=  (float)_pImage->Height();
					}

				}
			}
		}

	}

}
