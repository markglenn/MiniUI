#ifndef _MINIUI_INPUT_MOUSE_H_
#define _MINIUI_INPUT_MOUSE_H_

namespace MiniUI
{
	namespace Input
	{
		struct Mouse
		{
			Mouse ( ) : x(0), y(0), leftMouseDown(0), rightMouseDown(0) {}
			int x;
			int y;
			bool leftMouseDown;
			bool rightMouseDown;
		};
	}
}

#endif // _MINIUI_INPUT_MOUSE_H_
