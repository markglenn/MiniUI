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
		
		std::string ScreenName ( ) { return "ImageViewer"; }

		void OnShow ( );
	private:
		MiniUI::Widgets::Widget* _pMainWidget;		
		MiniUI::Widgets::Widget* _pSlideshow;
		
		MiniUI::Widgets::Widget* _pOnShowAnimation;
		MiniUI::Widgets::Widget* _pOnHideAnimation;
	};
}

#endif // _APPLICATIONS_IMAGEVIEWER_H_
