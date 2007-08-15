#include "GLRenderer.h"
#include "SDLImageResource.h"
#include <MiniUI/Host/HostIntegration.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <SDL/SDL.h>

using namespace MiniUI;
using namespace MiniUI::Graphics;
using namespace MiniUI::Types;
using namespace MiniUI::UISystem;
using namespace MiniUI::Input;

namespace OpenGLRenderer
{
	///////////////////////////////////////////////////////////////////////////
	GLRenderer::GLRenderer ( )
	///////////////////////////////////////////////////////////////////////////
	{
		Host::HostIntegration::Renderer = this;
		Host::HostIntegration::ResourceLoader = &_resourceLoader;
	}

	///////////////////////////////////////////////////////////////////////////
	GLRenderer::~GLRenderer ( )
	///////////////////////////////////////////////////////////////////////////
	{
		SDL_FreeSurface ( _pDisplaySurface );
		SDL_Quit ( );
		printf ("Done\n");
	}

	///////////////////////////////////////////////////////////////////////////
	bool GLRenderer::Initialize ( int width, int height )
	///////////////////////////////////////////////////////////////////////////
	{
		if ( SDL_Init ( SDL_INIT_VIDEO ) != 0 )
		{
			printf("Unable to initialize SDL: %s\n", SDL_GetError());
			return false;
		}

		// Enable Stencil and Double buffers
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 1);

		_pDisplaySurface = SDL_SetVideoMode ( width, height, 32, SDL_OPENGL | SDL_HWSURFACE );
		SDL_WM_SetCaption ( "miniUI", "" );

		glEnable ( GL_ARB_texture_non_power_of_two );
		glEnable ( GL_STENCIL_TEST );

		if ( _pDisplaySurface == NULL )
			return false;

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering

		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		glOrtho( 0, width, height, 0, 0, 1000 );
		glClearStencil ( 0  );

		glMatrixMode( GL_MODELVIEW );
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glEnable ( GL_STENCIL_TEST );

		// Setup the screen
		glLoadIdentity ( );
		glClearStencil(0);

		// Initialize blending
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return true;
	}

	///////////////////////////////////////////////////////////////////////////////
	void GLRenderer::Update ( UISystem::Screen* pScreen, Mouse *pMouse )
	///////////////////////////////////////////////////////////////////////////////
	{
		static int i = 0;

		i = ( i + 1 ) % 360;
		glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
		glLoadIdentity();

		UpdateWidgetList ( pScreen->GetWidgetList ( ), pMouse );

		SDL_GL_SwapBuffers();
	}

	///////////////////////////////////////////////////////////////////////////////
	void GLRenderer::UpdateWidgetList ( WidgetList *pList, Mouse *pMouse )
	///////////////////////////////////////////////////////////////////////////////
	{
		for ( WidgetList::iterator i = pList->begin(); i != pList->end(); i++ )
		{
			glPushMatrix ( );
			OpenGLRenderable* pRenderable = (OpenGLRenderable *)((*i)->GetRenderable ( ));

			glTranslatef ( pRenderable->centerPosition.x, pRenderable->centerPosition.y, 0 );
			glRotatef ( pRenderable->angle, 0.f, 0.f, 1.f );
			glTranslatef ( -pRenderable->centerPosition.x, -pRenderable->centerPosition.y, 0 );

			(*i)->HandleMouseInput ( pMouse );

			// Move into the correct position
			glTranslatef ( pRenderable->position.x, pRenderable->position.y, 0.f );
			glColor4f( 1.0f, 1.0f, 1.0f, pRenderable->opacity );

			glCallList ( pRenderable->GetDisplayList() );

			WidgetChildren::iterator j;
			WidgetChildren *pWidgetChildren = (*i)->GetWidgetChildren();
			for ( j = pWidgetChildren->begin(); j != pWidgetChildren->end(); j++ )
				UpdateChildArea ( &(*j), pMouse );

			glPopMatrix ( );
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	void GLRenderer::UpdateChildArea ( WidgetChildArea* pChildArea, Mouse *pMouse )
	///////////////////////////////////////////////////////////////////////////////
	{
		glPushMatrix ( );

		glTranslatef ( pChildArea->area.x, pChildArea->area.y, 0 );

		// Setup the stencil
		glColorMask(0,0,0,0);
		glStencilFunc(GL_EQUAL, pChildArea->depth, 0xFFFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);

		glBegin(GL_QUADS);
		{
			glVertex2i ( pChildArea->area.width, 0 );
			glVertex2i ( pChildArea->area.width,pChildArea->area.height );
			glVertex2i ( 0, pChildArea->area.height );
			glVertex2i ( 0, 0 );
		}
		glEnd ( );

		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

		glColorMask(1,1,1,1);

		// Only draw within parents window
		glStencilFunc(GL_EQUAL, pChildArea->depth + 1, 0xFFFF);

		// Draw the children
		UpdateWidgetList ( &pChildArea->children, pMouse );

		// Setup the stencil
		glColorMask(0,0,0,0);
		glStencilFunc(GL_EQUAL, pChildArea->depth + 1, 0xFFFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);

		// Clear out the stencil
		glBegin(GL_QUADS);
		{
			glVertex2i ( pChildArea->area.width, 0 );
			glVertex2i ( pChildArea->area.width, pChildArea->area.height );
			glVertex2i ( 0, pChildArea->area.height );
			glVertex2i ( 0, 0 );
		}
		glEnd ( );

		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glStencilFunc(GL_EQUAL, pChildArea->depth, 0xFFFF);
		glColorMask(1,1,1,1);

		glPopMatrix ( );
	}

}
