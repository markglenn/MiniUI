#ifndef _MINIUI_UISYSTEM_EVENTAREA_H_
#define _MINIUI_UISYSTEM_EVENTAREA_H_

#include "../Types/Rectangle.h"
#include <luabind/luabind.hpp>
#include <string>
#include <MiniUI/Input/Mouse.h>

namespace MiniUI
{
	namespace Widgets
	{
		class Widget;
		
		class EventArea
		{
		public:
			EventArea ( );
			virtual ~EventArea ( );
			std::string				id;
			Types::Rectangle<int>	area;

			void HandleMouse ( int x, int y, Input::Mouse* pMouse );

			virtual void OnMouseOver ( ) { }
			virtual void OnMouseOut ( ) { }
			virtual void OnMouseHover ( int x, int y ) { }
			virtual void OnMouseDown ( int x, int y ) { }
			virtual void OnMouseUp ( ) { }

			virtual void OnMouseMove ( int x, int y ) { }

			bool IsMouseOver;
			bool IsMouseDown;

			Widget* widget;
		};

		class EventArea_wrapper : public EventArea, public luabind::wrap_base
		{
		public:
			EventArea_wrapper() : EventArea()
			{}

			virtual void OnMouseOver ( )
			{
				call<void>("OnMouseOver");
			}
			static void default_OnMouseOver ( EventArea* ptr )
			{
				return ptr->EventArea::OnMouseOver( );
			}

			virtual void OnMouseOut ( )
			{
				call<void>("OnMouseOut");
			}
			static void default_OnMouseOut ( EventArea* ptr )
			{
				return ptr->EventArea::OnMouseOut( );
			}

			virtual void OnMouseHover ( int x, int y )
			{
				call<void>("OnMouseHover", x, y);
			}
			static void default_OnMouseHover ( EventArea* ptr, int x, int y )
			{
				return ptr->EventArea::OnMouseHover( x, y );
			}

			virtual void OnMouseDown ( int x, int y )
			{
				call<void>("OnMouseDown", x, y);
			}
			static void default_OnMouseDown ( EventArea* ptr, int x, int y )
			{
				return ptr->EventArea::OnMouseDown( x, y );
			}

			virtual void OnMouseUp ( )
			{
				call<void>("OnMouseUp");
			}
			static void default_OnMouseUp ( EventArea* ptr )
			{
				return ptr->EventArea::OnMouseUp( );
			}

			virtual void OnMouseMove ( int x, int y )
			{
				call<void>("OnMouseMove", x, y);
			}
			static void default_OnMouseMove ( EventArea* ptr, int x, int y )
			{
				return ptr->EventArea::OnMouseMove( x, y );
			}
		};

		typedef std::list <EventArea *> EventAreaList;
	}

}

#endif // _MINIUI_UISYSTEM_EVENTAREA_H_
