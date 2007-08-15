#ifndef _OPENGLRENDERER_GLRENDERER_H_
#define _OPENGLRENDERER_GLRENDERER_H_

#include <SDL/SDL.h>
#include <MiniUI/UIManager.h>
#include <MiniUI/Host/IRenderer.h>
#include <MiniUI/UISystem/Screen.h>
#include <MiniUI/Input/Mouse.h>

#include "ResourceLoader.h"
#include "OpenGLRenderable.h"

namespace OpenGLRenderer
{

	class GLRenderer : public MiniUI::Host::IRenderer
	{
	public:
		GLRenderer ( );
		virtual ~GLRenderer ( );

		bool Initialize ( int width, int height );

		virtual void Update ( MiniUI::UISystem::Screen* pScreen, MiniUI::Input::Mouse *pMouse );
		virtual MiniUI::Graphics::Renderable* CreateRenderable ( )
			{ return new OpenGLRenderable (); }

	private:
		void UpdateWidgetList ( MiniUI::Widgets::WidgetList *pList, MiniUI::Input::Mouse *pMouse );
		void UpdateChildArea ( MiniUI::Widgets::WidgetChildArea* pChildArea, MiniUI::Input::Mouse *pMouse );

		SDL_Surface	*_pDisplaySurface;
		ResourceLoader _resourceLoader;
	};
}

#endif // _OPENGLRENDERER_GLRENDERER_H_
