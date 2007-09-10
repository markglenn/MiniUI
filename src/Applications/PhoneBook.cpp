#include "PhoneBook.h"
#include "../ApplicationManager.h"

using namespace MiniUI;
using namespace MiniUI::UISystem;
using namespace MiniUI::Widgets;
using namespace MiniUI::LuaSystem;
using namespace luabind;

namespace Applications
{
	///////////////////////////////////////////////////////////////////////////
	PhoneBook::PhoneBook ( MiniUI::UIManager *pManager )
		: IApplication ( pManager ), _firstSelection ( 1 )
	///////////////////////////////////////////////////////////////////////////
	{
		_pListing = NULL;
	}
	
	///////////////////////////////////////////////////////////////////////////
	PhoneBook::~PhoneBook ( )
	///////////////////////////////////////////////////////////////////////////
	{
		
	}
	
	///////////////////////////////////////////////////////////////////////////
	void PhoneBook::OnShow ( )
	///////////////////////////////////////////////////////////////////////////
	{
		if ( _pListing == NULL )
		{
		
			Screen *pScreen = UIManager::Instance()->GetCurrentScreen();
			
			_pListing	= pScreen->FindWidget ( "PhoneListing" );
			_pSlider	= pScreen->FindWidget ( "Slider" );
			_pName		= pScreen->FindWidget ( "name" );
			_pPhone 	= pScreen->FindWidget ( "phone" );
			_pOnShowAnimation = pScreen->FindWidget ( "OnShow" );
			_pOnHideAnimation = pScreen->FindWidget ( "OnHide" );
			
			AddEntry ( "Jack Harten", "847-555-1212" );
			AddEntry ( "Andy Gabriel", "847-555-1212" );
			AddEntry ( "Angel Echevarria", "847-555-1212" );
			AddEntry ( "Keith Osik", "847-555-1212" );
			AddEntry ( "Doug Mast", "847-555-1212" );
			AddEntry ( "Alex Ramirez", "847-555-1212" );
			AddEntry ( "Mike Butcher", "847-555-1212" );
			AddEntry ( "Kevin Millar", "847-555-1212" );
			AddEntry ( "Brian Hiller", "847-555-1212" );
			AddEntry ( "Benny Agbayani", "847-555-1212" );
			AddEntry ( "Brian Daubach", "847-555-1212" );
			AddEntry ( "Lou Merloni", "847-555-1212" );
			AddEntry ( "Fred Rivers", "847-555-1212" );
			AddEntry ( "Charles Gipson", "847-555-1212" );
		}
				
		_pOnShowAnimation->CallVoid ( "Run" );
	}
	
	///////////////////////////////////////////////////////////////////////////
	void PhoneBook::OnEvent ( MiniUI::UIEvent* pEvent )
	///////////////////////////////////////////////////////////////////////////
	{
		std::string id = pEvent->pWidget->GetID( );
		
		if ( id == "PhoneListing" && pEvent->event == "OnSelect" )
		{
			_selectedIndex = object_cast<int>((*pEvent->parameter)["item"]);
			if ( _firstSelection )
				SlideInfoIn ( );
			else
				SlideInfoOut ( );
			
			_firstSelection = false;
		}
		if ( id == "Slider" && pEvent->event == "SlideOutDone" )
		{
			SlideInfoIn();
		}
			
		if ( id == "homeButton" && pEvent->event == "OnClick" )
		{
			_pOnHideAnimation->CallVoid( "Run" );
		}
		
		if ( id == "OnHide" && pEvent->event == "AnimationDone" )
			ApplicationManager::Instance()->ShowScreen("MainMenu");
	}
	
	///////////////////////////////////////////////////////////////////////////
	void PhoneBook::SlideInfoOut ( )
	///////////////////////////////////////////////////////////////////////////
	{
		_pSlider->Call ( "SlideOut", luabind::object() );
	}
	
	///////////////////////////////////////////////////////////////////////////
	void PhoneBook::SlideInfoIn ( )
	///////////////////////////////////////////////////////////////////////////
	{
		luabind::object object = newtable ( *LuaVirtualMachine::Instance() );
		
		object["text"] = "Name: " + _phoneBook[_selectedIndex].name;
		_pName->Call ( "ChangeText", object );
		
		object["text"] = "Phone: " + _phoneBook[_selectedIndex].phone;
		_pPhone->Call ( "ChangeText", object );
		
		_pSlider->Call ( "SlideIn", luabind::object() );
	}
	
	///////////////////////////////////////////////////////////////////////////
	void PhoneBook::AddEntry ( std::string name, std::string number )
	///////////////////////////////////////////////////////////////////////////
	{
		PhoneBookEntry entry = { name: name, phone: number };
		_phoneBook.push_back ( entry );
		luabind::object object = newtable ( *LuaVirtualMachine::Instance() );
		object["text"] = name;
		object["font"] = "MyFont";

		_pListing->Call ( "AddText", object );
	}
}
