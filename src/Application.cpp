//
// C++ Implementation: Application
//
// Description:
//
//
// Author: Mark Glenn <markglenn@gmail.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "Application.h"
#include "Integration/FileSystem/FolderArchive.h"
#include <MiniUI/Graphics/Renderable.h>
#include <MiniUI/UISystem/Screen.h>
#include <MiniUI/Types/Rectangle.h>
#include <MiniUI/Input/Mouse.h>
#include <SDL/SDL.h>

#include "Applications/MainMenu.h"
#include "Applications/ImageViewer.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

using namespace Integration;
using namespace Integration::FileSystem;
using namespace MiniUI;
using namespace MiniUI::Graphics;
using namespace MiniUI::Types;
using namespace MiniUI::Input;

using namespace Applications;

///////////////////////////////////////////////////////////////////////////////
Application::Application ( )
///////////////////////////////////////////////////////////////////////////////
{
	_pUIManager = new UIManager ( );
	_pMmanager = new Integration::MemoryManager ( );

	MiniUI::Host::HostIntegration::Memory = _pMmanager;
	_pUIManager->Initialize ( );
}

///////////////////////////////////////////////////////////////////////////////
Application::~Application()
///////////////////////////////////////////////////////////////////////////////
{
	delete _pUIManager;
	delete _pMmanager;
}

///////////////////////////////////////////////////////////////////////////////
bool Application::Initialize ( unsigned int width, unsigned int height )
///////////////////////////////////////////////////////////////////////////////
{
	_glRenderer.Initialize ( width, height );

	FolderArchive skinArchive ( "ui/" );
	_pUIManager->LoadUIArchive ( &skinArchive );

	// Load the test layout file
	FolderArchive archive ( "./" );
	_pUIManager->LoadScreens ( "test.xml", &archive );

	return true;
}

///////////////////////////////////////////////////////////////////////////////
bool Application::LoadUI ( std::string path )
///////////////////////////////////////////////////////////////////////////////
{
	FolderArchive archive ( path );

	return _pUIManager->LoadUIArchive ( &archive );
}

///////////////////////////////////////////////////////////////////////////////
void Application::Run ( )
///////////////////////////////////////////////////////////////////////////////
{
	ImageViewer imageViewer ( _pUIManager );
	
	imageViewer.Show ( );

	SDL_Event event;
	int ticks = SDL_GetTicks ( );

	Mouse mouse;

	while ( true )
	{
		while ( SDL_PollEvent ( &event ) )
		{
			switch ( event.type )
			{
				case SDL_QUIT:
					return;

				case SDL_MOUSEMOTION:
				{
					SDL_MouseMotionEvent* mouseEvent = (SDL_MouseMotionEvent *)&event;

					mouse.x = mouseEvent->x;
					mouse.y = 480 - mouseEvent->y;
				}
				break;

				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
				{
					SDL_MouseButtonEvent* buttonEvent = (SDL_MouseButtonEvent *)&event;

					if ( buttonEvent->button == SDL_BUTTON_LEFT )
						mouse.leftMouseDown = ( buttonEvent->type == SDL_MOUSEBUTTONDOWN );
					else if ( buttonEvent->button == SDL_BUTTON_RIGHT )
						mouse.rightMouseDown = ( buttonEvent->type == SDL_MOUSEBUTTONDOWN );
				}
				break;
			}

		}

		int currentTicks = SDL_GetTicks ( );
		_pUIManager->Update ( currentTicks - ticks, &mouse );
		
		ticks = currentTicks;
	}
	
	SDL_Quit ( );
}
