//
// C++ Interface: Application
//
// Description:
//
//
// Author: Mark Glenn <markglenn@gmail.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <MiniUI/UIManager.h>
#include <OpenGLRenderer/GLRenderer.h>
#include "Integration/MemoryManager.h"

/**
	@author Mark Glenn <markglenn@gmail.com>
*/
class Application
{
public:
	Application ( );
    ~Application ( );

	bool Initialize ( unsigned int width, unsigned int height );

	void Run ( );

private:
	bool InitRenderSystem ( );

	bool LoadUI ( std::string path );

	Integration::MemoryManager 	*_pMmanager;
	MiniUI::UIManager			*_pUIManager;
	OpenGLRenderer::GLRenderer	_glRenderer;
};

#endif // _APPLICATION_H_
