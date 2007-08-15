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

#ifndef _MINIUI_UISYSTEM_SKIN_H_
#define _MINIUI_UISYSTEM_SKIN_H_

#include <istream>
#include <map>
#include "../Host/IArchive.h"
#include <MiniUI/TinyXPath/tinyxml.h>

namespace MiniUI
{
	namespace UISystem
	{
		class Skin
		{
		public:
			Skin ( );
			virtual ~Skin ( );

			bool LoadSkinFile ( Host::IArchive *pArchive );

			TinyXPath::TiXmlElement* GetWidgetElement ( std::string id );

		private:
			void LoadFonts ( Host::IArchive *pArchive );
			TinyXPath::TiXmlDocument _skinDocument;
		};

	}
}

#endif // _MINIUI_UISYSTEM_SKIN_H_
