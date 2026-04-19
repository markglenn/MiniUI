cmake_minimum_required(VERSION 3.20)
project(miniui CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
# Put the executable next to the runtime assets (ui/, test.xml) in build/.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")

# Silence OpenGL / GLU deprecation warnings on macOS.
add_compile_definitions(GL_SILENCE_DEPRECATION BOOST_BIND_GLOBAL_PLACEHOLDERS)

# -------- Dependencies --------
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL12 REQUIRED IMPORTED_TARGET sdl)
# pkg-config gives -I/opt/homebrew/include/SDL but the code uses
# `<SDL/SDL.h>`, so also expose the prefix include dir.
pkg_get_variable(SDL12_PREFIX sdl prefix)
set(SDL12_PARENT_INCLUDE_DIR "${SDL12_PREFIX}/include")

find_package(OpenGL REQUIRED)

find_package(Boost REQUIRED)

# -------- Lua (C, built as a static lib) --------
set(LUA_SOURCES
    Lua/lapi.cpp Lua/lauxlib.cpp Lua/lbaselib.cpp Lua/lcode.cpp Lua/ldblib.cpp
    Lua/ldebug.cpp Lua/ldo.cpp Lua/ldump.cpp Lua/lfunc.cpp Lua/lgc.cpp Lua/linit.cpp
    Lua/liolib.cpp Lua/llex.cpp Lua/lmathlib.cpp Lua/lmem.cpp Lua/loadlib.cpp
    Lua/lobject.cpp Lua/lopcodes.cpp Lua/loslib.cpp Lua/lparser.cpp Lua/lstate.cpp
    Lua/lstring.cpp Lua/lstrlib.cpp Lua/ltable.cpp Lua/ltablib.cpp Lua/ltm.cpp
    Lua/lundump.cpp Lua/lvm.cpp Lua/lzio.cpp)
set_source_files_properties(${LUA_SOURCES} PROPERTIES LANGUAGE C)

add_library(lua STATIC ${LUA_SOURCES})
target_include_directories(lua PUBLIC ${CMAKE_SOURCE_DIR}/Lua)
target_compile_definitions(lua PRIVATE LUA_USE_MACOSX)

# -------- luabind (header-only Boost) --------
set(LUABIND_SOURCES
    luabind/class.cpp luabind/class_info.cpp luabind/class_registry.cpp
    luabind/class_rep.cpp luabind/create_class.cpp luabind/error.cpp
    luabind/find_best_match.cpp luabind/function.cpp luabind/implicit_cast.cpp
    luabind/link_compatibility.cpp luabind/object_rep.cpp luabind/open.cpp
    luabind/overload_rep.cpp luabind/pcall.cpp luabind/ref.cpp luabind/scope.cpp
    luabind/stack_content_by_name.cpp luabind/weak_ref.cpp luabind/wrapper_base.cpp)

add_library(luabind STATIC ${LUABIND_SOURCES})
target_include_directories(luabind PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Lua
    ${Boost_INCLUDE_DIRS})
target_link_libraries(luabind PUBLIC lua)

# -------- MiniUI core --------
set(MINIUI_SOURCES
    MiniUI/UIManager.cpp
    MiniUI/Types/Boolean.cpp MiniUI/Types/Float.cpp MiniUI/Types/Integer64.cpp MiniUI/Types/Integer.cpp
    MiniUI/UISystem/Skin.cpp MiniUI/UISystem/Screen.cpp MiniUI/UISystem/Font.cpp
    MiniUI/Animation/Animatable.cpp MiniUI/Animation/Animate.cpp MiniUI/Animation/Animator.cpp
    MiniUI/Animation/Delay.cpp MiniUI/Animation/EventNotify.cpp
    MiniUI/TinyXPath/action_store.cpp MiniUI/TinyXPath/lex_util.cpp MiniUI/TinyXPath/node_set.cpp
    MiniUI/TinyXPath/tinystr.cpp MiniUI/TinyXPath/tinyxml.cpp MiniUI/TinyXPath/tinyxmlerror.cpp
    MiniUI/TinyXPath/tinyxmlparser.cpp MiniUI/TinyXPath/tokenlist.cpp MiniUI/TinyXPath/xml_util.cpp
    MiniUI/TinyXPath/xpath_expression.cpp MiniUI/TinyXPath/xpath_processor.cpp
    MiniUI/TinyXPath/xpath_stack.cpp MiniUI/TinyXPath/xpath_static.cpp
    MiniUI/TinyXPath/xpath_stream.cpp MiniUI/TinyXPath/xpath_syntax.cpp
    MiniUI/LuaSystem/LuaVirtualMachine.cpp MiniUI/LuaSystem/Helper.cpp
    MiniUI/EventSystem/Event.cpp
    MiniUI/Graphics/Renderable.cpp MiniUI/Graphics/TextureManager.cpp
    MiniUI/Widgets/WidgetFactory.cpp MiniUI/Widgets/Widget.cpp
    MiniUI/Widgets/TextArea.cpp MiniUI/Widgets/Image.cpp)

add_library(miniui_core STATIC ${MINIUI_SOURCES})
target_include_directories(miniui_core PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Lua
    ${Boost_INCLUDE_DIRS})
target_link_libraries(miniui_core PUBLIC lua luabind PkgConfig::SDL12)

# -------- OpenGL renderer --------
add_library(OpenGLRenderer STATIC
    OpenGLRenderer/OpenGLRenderable.cpp
    OpenGLRenderer/SDLImageResource.cpp
    OpenGLRenderer/GLRenderer.cpp
    OpenGLRenderer/ResourceLoader.cpp)
target_include_directories(OpenGLRenderer PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party)
target_link_libraries(OpenGLRenderer PUBLIC
    miniui_core PkgConfig::SDL12 OpenGL::GL OpenGL::GLU)

# -------- SDL input --------
add_library(SDLInput STATIC SDLInput/SDLInputManager.cpp)
target_include_directories(SDLInput PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(SDLInput PUBLIC PkgConfig::SDL12)
target_include_directories(SDLInput PUBLIC ${SDL12_PARENT_INCLUDE_DIR})
target_include_directories(OpenGLRenderer PUBLIC ${SDL12_PARENT_INCLUDE_DIR})
target_include_directories(miniui_core PUBLIC ${SDL12_PARENT_INCLUDE_DIR})

# -------- Executable --------
add_executable(miniui
    src/miniui.cpp
    src/Application.cpp
    src/ApplicationManager.cpp
    src/Integration/MemoryManager.cpp
    src/Integration/FileSystem/FolderArchive.cpp
    src/Applications/PhoneBook.cpp
    src/Applications/IApplication.cpp
    src/Applications/MainMenu.cpp
    src/Applications/ImageViewer.cpp)

target_include_directories(miniui PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Lua
    ${Boost_INCLUDE_DIRS})

target_link_libraries(miniui PRIVATE
    OpenGLRenderer SDLInput ${CMAKE_DL_LIBS})
