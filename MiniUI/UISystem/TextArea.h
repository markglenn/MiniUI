#ifndef _MINIUI_UISYSTEM_TEXTAREA_H_
#define _MINIUI_UISYSTEM_TEXTAREA_H_

#include "Font.h"
#include "../Graphics/Renderable.h"
#include "Widget.h"

namespace MiniUI
{
	namespace UISystem
	{
		class TextArea : public Widget
		{
		public:
			TextArea ( );
			virtual ~TextArea ( );

			bool BuildText ( std::string text, Font* pFont, bool wordWrap = false, int width = 10000 );

			virtual void OnLoad ( TinyXPath::TiXmlElement *pSkin, TinyXPath::TiXmlElement *pLayout );

		private:
			std::string _text;
			bool 		_wordWrap;
			int 		_width;
			Font*		_pFont;
		};
	}

}

#endif // _MINIUI_UISYSTEM_TEXTAREA_H_
