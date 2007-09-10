#ifndef _APPLICATIONS_MAINMENU_H_
#define _APPLICATIONS_MAINMENU_H_

#include "IApplication.h"

namespace Applications
{
	class MainMenu : public IApplication
	{
	public:	
		MainMenu ( MiniUI::UIManager *pManager );
		virtual ~MainMenu ( );	
				
		void OnEvent ( MiniUI::UIEvent* pEvent );
		std::string ScreenName ( ) { return "MainMenu"; }
		
		void OnShow ( );
	private:

		void SlideMenus ( bool in );

		MiniUI::Widgets::Widget* _pOnShowAnim;
		MiniUI::Widgets::Widget* _pOnHideAnim;
		
		std::string _selectedItem;
		
	};
}

#endif // _APPLICATIONS_MAINMENU_H_
