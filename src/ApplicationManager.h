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
#ifndef _APPLICATIONMANAGER_H_
#define _APPLICATIONMANAGER_H_

#include <MiniUI/UIManager.h>
#include <MiniUI/Types/Singleton.h>

#include "Applications/IApplication.h"

#include <map>

class ApplicationManager : public MiniUI::Types::Singleton<ApplicationManager>
{
	public:
		ApplicationManager ( );
		~ApplicationManager ( );

		void Initialize ( );
		
		bool ShowScreen ( std::string id );

	private:
		typedef std::map <std::string, Applications::IApplication*> ApplicationMap;
		ApplicationMap _applications;
		
		Applications::IApplication *_selectedApp;
		void AddApplication ( Applications::IApplication *pApp );
};

#endif // _APPLICATIONMANAGER_H_
