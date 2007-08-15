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

#ifndef _MINIUI_UIMANAGER_H_
#define _MINIUI_UIMANAGER_H_

#include "LuaSystem/LuaVirtualMachine.h"
#include "Host/IArchive.h"
#include "Host/IMemory.h"
#include "Host/IResourceLoader.h"
#include "Input/Mouse.h"

#include "UISystem/Skin.h"
#include "UISystem/Screen.h"

#include "Graphics/TextureManager.h"

#include <map>
#include <string>

namespace MiniUI
{
	class UIManager
	{
	public:
		UIManager ( );
		virtual ~UIManager ( );

		bool LoadUIArchive ( Host::IArchive *pArchive );
		bool LoadScreens ( std::string rootXML, Host::IArchive *pArchive );

		bool Initialize (  );

		bool Update ( unsigned int timestep, Input::Mouse* pMouse );

		void SetCurrentScreen ( std::string name ) { _pCurrentScreen = _screens[name]; }
		UISystem::Screen* GetCurrentScreen ( ) { return _pCurrentScreen; }


	private:
		typedef std::map<std::string, UISystem::Screen*> ScreenMap;
		bool InitializeScripts ( );

		void UpdateWidget ( UISystem::WidgetList* pWidgetList, int timestep, Input::Mouse* pMouse );

		LuaSystem::LuaVirtualMachine 	_luaVM;
		UISystem::Skin					_skin;
		UISystem::Screen*				_pCurrentScreen;

		ScreenMap 						_screens;
		Graphics::TextureManager		_textureManager;
	};

}

#endif // _MINIUI_UIMANAGER_H_
