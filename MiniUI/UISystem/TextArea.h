#ifndef _MINIUI_UISYSTEM_TEXTAREA_H_
#define _MINIUI_UISYSTEM_TEXTAREA_H_

#include "Font.h"
#include "../Graphics/Renderable.h"

namespace MiniUI
{
	namespace UISystem
	{
		class TextArea
		{
		public:
			TextArea ( );
			virtual ~TextArea ( );

			bool BuildText ( std::string text, Font* pFont, bool wordWrap = false, int width = 10000 );

		private:
			std::string _text;
			bool 		_wordWrap;
			int 		_width;
			Font*		_pFont;

			Graphics::Renderable* _pRenderable;
		};
	}

}

#endif // _MINIUI_UISYSTEM_TEXTAREA_H_
