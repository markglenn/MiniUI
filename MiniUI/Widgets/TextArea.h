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

			virtual void OnLoad ( TinyXPath::TiXmlElement *pSkin, TinyXPath::TiXmlElement *pLayout );

		private:
			std::string 	_text;
			bool 			_wordWrap;
			int 			_width;
			UISystem::Font*	_pFont;
		};
	}

}

#endif // _MINIUI_UISYSTEM_TEXTAREA_H_
