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

#ifndef _LUAVIRTUALMACHINE_H_
#define _LUAVIRTUALMACHINE_H_

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "../Types/Singleton.h"
#include <string>

#include "../Host/IArchive.h"

namespace MiniUI
{
	namespace LuaSystem
	{
		class LuaVirtualMachine : public Types::Singleton<LuaVirtualMachine>
		{
		public:
			LuaVirtualMachine ( );
			virtual ~LuaVirtualMachine ( );

			operator lua_State *() { return m_pState; }

			// Loads a lua file
			bool LoadScript ( std::string filename, Host::IArchive* pArchive );
			bool LoadScriptBuffer ( std::string scriptBuffer );

			bool Running () { return m_pState != NULL; }

			void LoadLibs ( ) { luaL_openlibs ( m_pState ); }

			void** CreateObject ( std::string className );
			int CreateLuaObject ( std::string className );
			void ReleaseLuaObject ( int reference );

			bool SetupCallFunction ( int object, std::string funcName );
			void ClearStack ( );
			void StackDump ( );
		private:


			lua_State *m_pState;
		};
	}
}

#endif // _LUAVIRTUALMACHINE_H_
