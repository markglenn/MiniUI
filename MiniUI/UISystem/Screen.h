//
// C++ Interface: Screen
//
// Description:
//
//
// Author: Mark Glenn <markglenn@gmail.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef MINIUI_UISYSTEMSCREEN_H
#define MINIUI_UISYSTEMSCREEN_H

#include <list>

#include "../TinyXPath/tinyxml.h"
#include "../Graphics/Renderable.h"
#include "Widget.h"

namespace MiniUI
{
	namespace UISystem
	{
		class Skin;

		class Screen
		{
		public:
			Screen();
			virtual ~Screen();

			bool LoadScreen ( TinyXPath::TiXmlElement *pElement );
			bool BuildScreen ( Skin* pSkin );

			std::string id ( ) { return _id; }
			WidgetList* GetWidgetList ( ) { return &_widgetList; }

		protected:
			Widget*	LoadWidget ( TinyXPath::TiXmlElement* pChild, Skin* pSkin, int depth = 0 );

			bool LoadLayout ( Graphics::Renderable* pRenderable,
							  TinyXPath::TiXmlElement* pChild, TinyXPath::TiXmlElement* pWidget );

			bool LoadChildren ( Widget* pWidget, TinyXPath::TiXmlElement* pChild,
								TinyXPath::TiXmlElement* pWidgetEl, Skin* pSkin, int depth );

			bool LoadEventAreas ( Widget* pWidget, TinyXPath::TiXmlElement* pChild,
								  TinyXPath::TiXmlElement* pWidgetEl );

			void OnLayout ( WidgetList *pWidgetList );

		private:

			std::string _id;
			TinyXPath::TiXmlElement*	_pElement;
			WidgetList				 	_widgetList;
		};

	}

}

#endif // MINIUI_UISYSTEMSCREEN_H
