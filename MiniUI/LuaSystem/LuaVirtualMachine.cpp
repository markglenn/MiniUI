#include "LuaVirtualMachine.h"
#include "../Host/IArchive.h"
#include "../Host/HostIntegration.h"
#include "../Host/IMemory.h"
#include "../Types/Vector2D.h"
#include <luabind/luabind.hpp>
#include <luabind/adopt_policy.hpp>
#include <MiniUI/Widgets/Widget.h>

#include <MiniUI/TinyXPath/tinyxml.h>
#include <MiniUI/TinyXPath/xpath_static.h>

#include <MiniUI/Animation/Animator.h>
#include <MiniUI/Animation/Animate.h>
#include <MiniUI/Animation/Delay.h>
#include <MiniUI/Animation/EventNotify.h>


using MiniUI::Host::IArchive;
using MiniUI::Host::IResource;
using namespace MiniUI::Widgets;
using namespace MiniUI::Types;
using namespace MiniUI::TinyXPath;
using namespace MiniUI::Animation;

using namespace luabind;
using namespace std;

namespace MiniUI
{
	namespace LuaSystem
	{

		int add_file_and_line(lua_State* L)
		{
			lua_Debug d;
			lua_getstack(L, 1, &d);
			lua_getinfo(L, "Sln", &d);
			std::string err = lua_tostring(L, -1);
			lua_pop(L, 1);
			std::stringstream msg;
			msg << d.short_src << ":" << d.currentline;

			if (d.name != 0)
			{
				msg << "(" << d.namewhat << " " << d.name << ")";
			}
			msg << " " << err;
			lua_pushstring(L, msg.str().c_str());

			return 1;
		}

		///////////////////////////////////////////////////////////////////////
		TiXmlElement* xpath_element ( const TiXmlElement* pElement, const char* path )
		///////////////////////////////////////////////////////////////////////
		{
			return (TiXmlElement* )XNp_xpath_node ( pElement, path );
		}

		///////////////////////////////////////////////////////////////////////
		std::string xpath_string ( const TiXmlElement* pElement, const char* path )
		///////////////////////////////////////////////////////////////////////
		{
			return S_xpath_string ( pElement, path );
		}

		///////////////////////////////////////////////////////////////////////
		double xpath_number ( const TiXmlElement* pElement, std::string path )
		///////////////////////////////////////////////////////////////////////
		{
			return d_xpath_double ( pElement, path.c_str() );
		}

		///////////////////////////////////////////////////////////////////////
		void LuaVirtualMachine::StackDump ( )
		///////////////////////////////////////////////////////////////////////
		{
			int i;
			int top = lua_gettop(m_pState);
			for (i = 1; i <= top; i++)
			{
				/* repeat for each level */
				int t = lua_type(m_pState, i);
				switch (t)
				{

					case LUA_TSTRING: /* strings */
						printf("`%s'", lua_tostring(m_pState, i));
						break;

					case LUA_TBOOLEAN: /* booleans */
						printf(lua_toboolean(m_pState, i) ? "true" : "false");
						break;

					case LUA_TNUMBER: /* numbers */
						printf("%g", lua_tonumber(m_pState, i));
						break;

					case LUA_TUSERDATA:
						printf("Userdata: %8x", lua_touserdata(m_pState, i));
						break;

					default: /* other values */
						printf("%s", lua_typename(m_pState, t));
						break;

				}
				printf("\n "); /* put a separator */
			}
			printf("\n---\n"); /* end the listing */
		}

		///////////////////////////////////////////////////////////////////////
		void LuaVirtualMachine::ClearStack ( )
		///////////////////////////////////////////////////////////////////////
		{
			// clean up lua stack
			lua_pop( m_pState, lua_gettop( m_pState ) );

		}

		///////////////////////////////////////////////////////////////////////
		void *LVMAllocate ( void *, void *ptr, size_t, size_t nsize )
		///////////////////////////////////////////////////////////////////////
		{
			if ( nsize == 0 )
			{
				Host::HostIntegration::Memory->Deallocate ( ptr );
				return NULL;
			}

			return Host::HostIntegration::Memory->Reallocate ( ptr, nsize );
		}

		///////////////////////////////////////////////////////////////////////
		LuaVirtualMachine::LuaVirtualMachine ( )
		///////////////////////////////////////////////////////////////////////
		{
			m_pState = luaL_newstate ( );
			//lua_setallocf ( m_pState, LVMAllocate, NULL );

			luaL_openlibs(m_pState);
			// Setup the classes

			luabind::open(m_pState);
			set_pcall_callback(add_file_and_line);
			module(m_pState)
			[
				class_<EventArea, EventArea_wrapper>("EventArea")
				.def(constructor<>())
				.def("OnMouseOver", &EventArea::OnMouseOver, &EventArea_wrapper::default_OnMouseOver)
				.def("OnMouseOut", &EventArea::OnMouseOut, &EventArea_wrapper::default_OnMouseOut)
				.def("OnMouseHover", &EventArea::OnMouseHover, &EventArea_wrapper::default_OnMouseHover)
				.def("OnMouseUp", &EventArea::OnMouseUp, &EventArea_wrapper::default_OnMouseUp)
				.def("OnMouseDown", &EventArea::OnMouseDown, &EventArea_wrapper::default_OnMouseDown)
				.def("OnMouseMove", &EventArea::OnMouseMove, &EventArea_wrapper::default_OnMouseMove)
				.def_readonly("widget", &EventArea::widget),

				class_< Vector2D<int> >("Vector2D")
				.def(constructor<int,int>())
				.def_readwrite("x", &Vector2D<int>::x)
				.def_readwrite("y", &Vector2D<int>::y),

				class_<TinyXPath::TiXmlElement>("TiXmlElement")
			];
			Widget::RegisterWithLua (this);
			
			Animatable::RegisterWithLua (this);
			Animator::RegisterWithLua (this);
			Animate::RegisterWithLua (this);
			Delay::RegisterWithLua (this);
			EventNotify::RegisterWithLua (this);
			
			module(m_pState, "xpath")
			[
				def ("ToElement", &xpath_element, adopt(result)),
				def ("ToString", &xpath_string),
				def ("ToNumber", &xpath_number)
			];

		}

		///////////////////////////////////////////////////////////////////////
		LuaVirtualMachine::~LuaVirtualMachine ( )
		///////////////////////////////////////////////////////////////////////
		{
			if ( Running ( ) )
				lua_close ( m_pState );
		}

		///////////////////////////////////////////////////////////////////////
		bool LuaVirtualMachine::LoadScript ( std::string filename,
			IArchive *pArchive )
		///////////////////////////////////////////////////////////////////////
		{
			std::istream* pStream = pArchive->LoadFile ( filename );

			// Did the file load?
			if ( pStream != NULL )
			{
				string script = "";

				while ( !pStream->eof() )
				{
					string scriptline;
					getline ( *pStream, scriptline );

					script += scriptline + "\n";
				}
				delete pStream;

				return LoadScriptBuffer ( script );
			}

			// Couldn't find the file
			return false;

		}

		///////////////////////////////////////////////////////////////////////
		bool LuaVirtualMachine::LoadScriptBuffer ( std::string scriptBuffer )
		///////////////////////////////////////////////////////////////////////
		{
			if ( luaL_dostring ( m_pState, scriptBuffer.c_str() ) )
				printf ("Lua Error: %s\n", lua_tostring(m_pState, -1));
		}

		///////////////////////////////////////////////////////////////////////
		void** LuaVirtualMachine::CreateObject ( std::string className )
		///////////////////////////////////////////////////////////////////////
		{
			lua_getglobal( m_pState, className.c_str() );

			// Make sure we found a script for this widget
			if ( lua_isnil(m_pState, -1) )
				return NULL;

			// Call the 'new' method
			lua_pushstring( m_pState, "new" );
			lua_gettable ( m_pState, -2 );
			lua_getglobal( m_pState, className.c_str() );

			// Call the method
			if ( lua_pcall(m_pState, 1, 1, 0) != 0 )
			{
				printf( "Error: %s", lua_tostring(m_pState, -1) );
				ClearStack ( );
				return NULL;
			}

			void** pObject = static_cast<void**>(lua_touserdata(m_pState, 2));

			ClearStack ( );

			return pObject;
		}

		///////////////////////////////////////////////////////////////////////
		int LuaVirtualMachine::CreateLuaObject ( std::string className )
		///////////////////////////////////////////////////////////////////////
		{
			lua_getglobal( m_pState, className.c_str() );

			// Make sure we found a script for this widget
			if ( lua_isnil(m_pState, -1) )
			{
				ClearStack ( );
				return 0;
			}

			// Call the method
			if ( lua_pcall(m_pState, 0, 1, 0) != 0 )
			{
				printf( "Error: %s", lua_tostring(m_pState, -1) );
				ClearStack ( );
				return 0;
			}

			// Get a reference to this object
			int ref = luaL_ref ( m_pState, LUA_REGISTRYINDEX );

			ClearStack();

			return ref;
		}

		///////////////////////////////////////////////////////////////////////
		void LuaVirtualMachine::ReleaseLuaObject ( int reference )
		///////////////////////////////////////////////////////////////////////
		{
			luaL_unref ( m_pState, LUA_REGISTRYINDEX, reference );
		}

		///////////////////////////////////////////////////////////////////////
		bool LuaVirtualMachine::SetupCallFunction ( int object, std::string funcName )
		///////////////////////////////////////////////////////////////////////
		{
			// No lua widget
			if ( object == 0 )
				return false;

			ClearStack();
			lua_rawgeti ( m_pState, LUA_REGISTRYINDEX, object );

			lua_pushstring( m_pState, funcName.c_str() );
			lua_gettable ( m_pState, -2 );
			lua_rawgeti ( m_pState, LUA_REGISTRYINDEX, object );

			if ( lua_isnil(m_pState, -1) )
			{
				ClearStack ( );
				return false;
			}

			return true;
		}
	}

}
