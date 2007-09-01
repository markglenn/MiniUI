#include "MainMenu.h"

using namespace MiniUI;
using namespace MiniUI::Widgets;
using namespace MiniUI::LuaSystem;
using namespace luabind;

namespace Applications
{
	///////////////////////////////////////////////////////////////////////////
	MainMenu::MainMenu ( MiniUI::UIManager *pManager )
		: IApplication ( pManager )
	///////////////////////////////////////////////////////////////////////////
	{
		pManager->SetCurrentScreen ( "PictureViewer" );
		
		Widget *pShutdown = pManager->GetCurrentScreen()->FindWidget ( "shutdownButton" );
		_pMenu = pManager->GetCurrentScreen()->FindWidget ( "animatedMenu" );
	}
	
	///////////////////////////////////////////////////////////////////////////
	MainMenu::~MainMenu ( )
	///////////////////////////////////////////////////////////////////////////
	{
		
	}
	
	///////////////////////////////////////////////////////////////////////////
	void MainMenu::OnEvent ( MiniUI::UIEvent* pEvent )
	///////////////////////////////////////////////////////////////////////////
	{
		luabind::object object = newtable ( *LuaVirtualMachine::Instance() );
		object["id"] = "shutdownOverlay";
		
		if ( pEvent->pWidget->GetID() == "shutdownButton" )
			_pMenu->Call ("select", object);
	}
}
