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

#ifndef _MINIUI_UISYSTEM_TEXTAREA_H_
#define _MINIUI_UISYSTEM_TEXTAREA_H_

#include <MiniUI/UISystem/Font.h>
#include "../Graphics/Renderable.h"
#include "Widget.h"

namespace MiniUI
{
	namespace Widgets
	{
		class TextArea : public Widget
		{
		public:
			TextArea ( );
			virtual ~TextArea ( );

			bool BuildText ( std::string text, UISystem::Font* pFont, bool wordWrap = false, int width = 10000 );
			virtual void Call ( std::string func, luabind::object object );
			virtual void OnLoad ( TinyXPath::TiXmlElement *pSkin, TinyXPath::TiXmlElement *pLayout );
			void ChangeString ( std::string text );
			
		private:
			std::string 	_text;
			bool 			_wordWrap;
			int 			_width;
			UISystem::Font*	_pFont;
		};
	}

}

#endif // _MINIUI_UISYSTEM_TEXTAREA_H_
