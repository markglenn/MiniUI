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

#ifndef _MINIUI_HOST_IRENDERER_H_
#define _MINIUI_HOST_IRENDERER_H_

#include <MiniUI/UISystem/Screen.h>
#include <MiniUI/Graphics/Renderable.h>
#include <MiniUI/Input/Mouse.h>

namespace MiniUI
{
	namespace Host
	{
		class IRenderer
		{
		public:
			virtual void Update ( UISystem::Screen* pScreen,
				Input::Mouse *pMouse ) = 0;
			virtual Graphics::Renderable* CreateRenderable ( ) = 0;
		};
	}

}

#endif // _MINIUI_HOST_IRENDERER_H_
