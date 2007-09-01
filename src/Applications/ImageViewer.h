#ifndef _APPLICATIONS_IMAGEVIEWER_H_
#define _APPLICATIONS_IMAGEVIEWER_H_

#include "IApplication.h"

namespace Applications
{
	class ImageViewer : public IApplication
	{
	public:	
		ImageViewer ( MiniUI::UIManager *pManager );
		virtual ~ImageViewer ( );	
				
		void OnEvent ( MiniUI::UIEvent* pEvent );
	private:
		MiniUI::Widgets::Widget* _pMainWidget;		
		MiniUI::Widgets::Widget* _pSlideshow;		
	};
}

#endif // _APPLICATIONS_IMAGEVIEWER_H_
