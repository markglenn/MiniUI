#include "ImageViewer.h"

using namespace MiniUI;
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
		pManager->SetCurrentScreen ( "PictureViewer" );
		
		_pMainWidget = pManager->GetCurrentScreen()->FindWidget ( "pictureViewer" );
		_pSlideshow = pManager->GetCurrentScreen()->FindWidget ( "slideShow" );
	}
	
	///////////////////////////////////////////////////////////////////////////
	ImageViewer::~ImageViewer ( )
	///////////////////////////////////////////////////////////////////////////
	{
		
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
	}
}
