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
	};
}

#endif // _APPLICATIONS_MAINMENU_H_
