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

#include "Skin.h"
#include <string>

#include "../TinyXPath/xpath_static.h"
#include "Font.h"

using namespace std;
using namespace MiniUI::TinyXPath;
using namespace MiniUI::Host;

namespace MiniUI
{
	namespace UISystem
	{
		///////////////////////////////////////////////////////////////////////
		Skin::Skin ( )
		///////////////////////////////////////////////////////////////////////
		{

		}

		///////////////////////////////////////////////////////////////////////
		Skin::~Skin ( )
		///////////////////////////////////////////////////////////////////////
		{

		}

		///////////////////////////////////////////////////////////////////////
		bool Skin::LoadSkinFile ( IArchive *pArchive )
		///////////////////////////////////////////////////////////////////////
		{
			std::istream* pStream = pArchive->LoadFile ( "skin.xml" );

			// File exists?
			if ( pStream == NULL )
				return false;

			string xmlData;

			while ( !pStream->eof() )
			{
				string xmlLine;
				getline ( *pStream, xmlLine );

				xmlData += xmlLine + "\n";
			}

			_skinDocument.Parse ( xmlData.c_str() );

			LoadFonts ( pArchive );
			delete pStream;
			return true;
		}

		///////////////////////////////////////////////////////////////////////
		TiXmlElement* Skin::GetWidgetElement ( std::string id )
		///////////////////////////////////////////////////////////////////////
		{
			std::string widgetPath = "/skin/widgets/widget[@id='" + id + "']";
			return (TiXmlElement *)XNp_xpath_node ( _skinDocument.FirstChildElement(),
					widgetPath.c_str() );
		}
		
		///////////////////////////////////////////////////////////////////////
		void Skin::LoadFonts ( IArchive *pArchive )
		///////////////////////////////////////////////////////////////////////
		{
			// Find the fonts used in this skin
			xpath_processor xpath ( _skinDocument.FirstChildElement(), 
					"/skin/fonts/font" );

			// Loop through all the sections
			int numFonts = xpath.u_compute_xpath_node_set ( );
			for ( int i = 0; i < numFonts; i++ )
			{
				TiXmlElement* pFontElement = 
						(TiXmlElement*)xpath.XNp_get_xpath_node ( i );
				
				Font::LoadFont ( pFontElement, pArchive );
			}

		}
	}

}
