//
// C++ Interface: Font
//
// Description:
//
//
// Author: Mark Glenn <markglenn@gmail.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef MINIUI_UISYSTEMFONT_H
#define MINIUI_UISYSTEMFONT_H

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#include "../Host/IArchive.h"
#include "../Graphics/ImageResource.h"
#include "../Graphics/Renderable.h"
#include "../TinyXPath/xpath_processor.h"

namespace MiniUI
{
	namespace UISystem
	{

		/**
			@author Mark Glenn <markglenn@gmail.com>
		*/
		class Font
		{
		public:
			Font ( );
			~Font ( );

			static bool LoadFont ( TinyXPath::TiXmlElement* pElement, Host::IArchive *pArchive );
			static Font* GetFont ( std::string name );
			
			bool LoadFont ( std::string name, Host::IArchive *pArchive );
			
			void SetName ( std::string name ) { _name = name; }
			std::string Name ( ) { return _name; }

			Graphics::GraphicalRect GetCharacter ( char c ) { return _characters[c]; }
			Graphics::ImageResource* GetImageResource ( ) { return _pImage; }

			void SetImageResource ( Graphics::ImageResource* pImage );
			
			typedef std::map<std::string, boost::shared_ptr<Font> > FontListType;
			static FontListType FontList;
			
		private:

			Graphics::ImageResource* LoadImage ( std::string path, Host::IArchive* pArchive );

			void ConvertToCharacters ( );

			std::string _name;
			std::string _sourceImage;

			typedef struct
			{
				unsigned int 	x;
				unsigned int	y;
				unsigned int	cellX;
				unsigned int	cellY;
				unsigned char	bpp;
				unsigned char 	base;
			} FontHeader;

			char 						_widths[256];
			Graphics::GraphicalRect		_characters[256];
			Graphics::ImageResource*	_pImage;
			FontHeader					_header;


		};

	}

}

#endif
