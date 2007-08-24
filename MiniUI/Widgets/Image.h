#ifndef _MINIUI_UISYSTEM_IMAGE_H_
#define _MINIUI_UISYSTEM_IMAGE_H_

#include "../Graphics/Renderable.h"
#include "Widget.h"

namespace MiniUI
{
	namespace Widgets
	{
		class Image : public Widget
		{
		public:
			Image ( );
			virtual ~Image ( );

			virtual void OnLoad ( TinyXPath::TiXmlElement *pSkin, TinyXPath::TiXmlElement *pLayout );

		private:
		
		};
	}

}

#endif // _MINIUI_UISYSTEM_IMAGE_H_
