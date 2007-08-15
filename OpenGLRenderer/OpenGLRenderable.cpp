#include <GL/glu.h>
#include <MiniUI/Types/Vector2D.h>

#include "OpenGLRenderable.h"
#include "SDLImageResource.h"

using namespace MiniUI::Graphics;
using namespace MiniUI::Types;

namespace OpenGLRenderer
{
	///////////////////////////////////////////////////////////////////////////
	OpenGLRenderable::OpenGLRenderable ( )
	///////////////////////////////////////////////////////////////////////////
	{
		_drawDisplayList = glGenLists ( 1 )	;
		image = 0;
		opacity = 1.0f;
	}

	///////////////////////////////////////////////////////////////////////////
	OpenGLRenderable::~OpenGLRenderable ( )
	///////////////////////////////////////////////////////////////////////////
	{

	}

	///////////////////////////////////////////////////////////////////////////
	void OpenGLRenderable::OnChanged ( )
	///////////////////////////////////////////////////////////////////////////
	{
		// Update our display lists
		glNewList( _drawDisplayList, GL_COMPILE );

		// Set the image
		if ( image )
			glBindTexture ( GL_TEXTURE_2D, (( SDLImageResource * )( image ))->GetTexture() );

		// Draw the current widget
		GraphicalRectIterator i;
		for ( i = begin(); i != end(); i++ )
		{
			if ( !((*i).isVisible) )
				continue;

			// Draw each section's quad
			glBegin(GL_QUADS);
			for (int j =0 ; j < 4; j++ )
			{
				glTexCoord2f ( (*i).coordinates[j].texture.x, (*i).coordinates[j].texture.y );
				glVertex2i ( (*i).coordinates[j].position.x, (*i).coordinates[j].position.y );
			}
			glEnd();
		}

		glEndList ( );
	}

	///////////////////////////////////////////////////////////////////////////
	Vector2D<int> OpenGLRenderable::GetTranslatedPosition ( int x, int y )
	///////////////////////////////////////////////////////////////////////////
	{
		Vector2D<GLdouble> transPositionDouble;
		GLdouble z;

		// arrays to hold matrix information
		GLdouble model_view[16];
		glGetDoublev(GL_MODELVIEW_MATRIX, model_view);

		GLdouble projection[16];
		glGetDoublev(GL_PROJECTION_MATRIX, projection);

		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);

		// get 3D coordinates based on window coordinates

		gluUnProject( x, y, 0.0, model_view, projection, viewport,
					  &transPositionDouble.x, &transPositionDouble.y, &z);

		int _x = (int)transPositionDouble.x - this->position.x;
		int _y = (int)transPositionDouble.y - this->position.y;

		// Are we inside?
		return Vector2D<int> ( _x, _y );
	}
}
