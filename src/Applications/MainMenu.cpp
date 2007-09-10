#include "MainMenu.h"
#include "../ApplicationManager.h"

using namespace MiniUI;
using namespace MiniUI::UISystem;
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
		_pOnShowAnim = 0;
	}
	
	///////////////////////////////////////////////////////////////////////////
	MainMenu::~MainMenu ( )
	///////////////////////////////////////////////////////////////////////////
	{
		
	}
	
	///////////////////////////////////////////////////////////////////////////
	void MainMenu::OnShow ( )
	///////////////////////////////////////////////////////////////////////////
	{
		if ( _pOnShowAnim == NULL )
		{
		
			Screen *pScreen = UIManager::Instance()->GetCurrentScreen();
			
			_pOnShowAnim = pScreen->FindWidget ( "OnShow" );
			_pOnHideAnim = pScreen->FindWidget ( "OnHide" );
		}
				
		SlideMenus ( true );
	}
	
	///////////////////////////////////////////////////////////////////////////
	void MainMenu::SlideMenus ( bool in )
	///////////////////////////////////////////////////////////////////////////
	{
		if ( in )
			_pOnShowAnim->Call ( "Run", luabind::object() );
		else
			_pOnHideAnim->Call ( "Run", luabind::object() );
	}
	
	///////////////////////////////////////////////////////////////////////////
	void MainMenu::OnEvent ( MiniUI::UIEvent* pEvent )
	///////////////////////////////////////////////////////////////////////////
	{	
		std::string id = pEvent->pWidget->GetID () ;
		
		if ( pEvent->event == "OnClick" )
			if ( id == "phoneBookSelect" || id == "imageViewerSelect" )
			{
				_selectedItem = id;
				SlideMenus ( false );
			}
		
		if ( pEvent->event == "AnimationDone" && id=="OnHide")
		{
			if ( _selectedItem == "phoneBookSelect" )
				ApplicationManager::Instance()->ShowScreen ( "PhoneBook" );
			else if ( _selectedItem == "imageViewerSelect" )
				ApplicationManager::Instance()->ShowScreen ( "ImageViewer" );
		}
	}
}
