#ifndef _OPENGLRENDERABLE_H_
#define _OPENGLRENDERABLE_H_

#include <MiniUI/Graphics/Renderable.h>
#include <MiniUI/Types/Vector2D.h>
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#else
#  include <GL/gl.h>
#endif

namespace OpenGLRenderer
{
	class OpenGLRenderable : public MiniUI::Graphics::Renderable
	{
	public:
		OpenGLRenderable ( );
		virtual ~OpenGLRenderable ( );

		virtual void OnChanged ( );

		inline GLuint GetDisplayList ( ) { return _drawDisplayList; }
		virtual MiniUI::Types::Vector2D<int> GetTranslatedPosition ( int x, int y );
	private:
		GLuint _drawDisplayList;

	};
}

#endif // _OPENGLRENDERABLE_H_
