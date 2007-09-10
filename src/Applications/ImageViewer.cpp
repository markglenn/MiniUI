#include "ImageViewer.h"
#include "../ApplicationManager.h"

using namespace MiniUI;
using namespace MiniUI::UISystem;
using namespace MiniUI::Widgets;
using namespace MiniUI::LuaSystem;
using namespace luabind;

namespace Applications
{
	///////////////////////////////////////////////////////////////////////////
	ImageViewer::ImageViewer ( MiniUI::UIManager *pManager )
		: IApplication ( pManager )
	///////////////////////////////////////////////////////////////////////////
	{
		_pMainWidget = NULL;
		_pSlideshow = NULL;
	}
	
	///////////////////////////////////////////////////////////////////////////
	ImageViewer::~ImageViewer ( )
	///////////////////////////////////////////////////////////////////////////
	{
		
	}
	
	///////////////////////////////////////////////////////////////////////////
	void ImageViewer::OnShow ( )
	///////////////////////////////////////////////////////////////////////////
	{
		if ( _pMainWidget == NULL )
		{
			Screen *pScreen = UIManager::Instance()->GetCurrentScreen();
			
			_pMainWidget = pScreen->FindWidget ( "pictureViewer" );
			_pSlideshow = pScreen->FindWidget ( "slideShow" );
			_pOnShowAnimation = pScreen->FindWidget ( "OnShow" );
			_pOnHideAnimation = pScreen->FindWidget ( "OnHide" );
		}
		
		_pOnShowAnimation->CallVoid ( "Run" );
		
	}
	
	///////////////////////////////////////////////////////////////////////////
	void ImageViewer::OnEvent ( MiniUI::UIEvent* pEvent )
	///////////////////////////////////////////////////////////////////////////
	{
		std::string id = pEvent->pWidget->GetID( );
		
		if ( id == "nextButton" )
		{
			_pMainWidget->Call ( "Animate", luabind::object() );
			_pSlideshow->Call ( "NextImage", luabind::object() );
		}
		if ( id == "previousButton" )
		{
			_pMainWidget->Call ( "Animate", luabind::object() );
			_pSlideshow->Call ( "PreviousImage", luabind::object() );
		}	
			
		if ( id == "homeButton" && pEvent->event == "OnClick" )
		{
			_pOnHideAnimation->CallVoid( "Run" );
		}
		
		if ( id == "OnHide" && pEvent->event == "AnimationDone" )
			ApplicationManager::Instance()->ShowScreen("MainMenu");
	}
}
