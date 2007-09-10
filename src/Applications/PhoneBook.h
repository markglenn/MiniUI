#ifndef _APPLICATIONS_PHONEBOOK_H_
#define _APPLICATIONS_PHONEBOOK_H_

#include "IApplication.h"

namespace Applications
{
	class PhoneBook : public IApplication
	{
	public:	
		PhoneBook ( MiniUI::UIManager *pManager );
		virtual ~PhoneBook ( );
				
		void OnEvent ( MiniUI::UIEvent* pEvent );
		std::string ScreenName ( ) { return "PhoneBook"; }
		void OnShow ( );

	private:
		
		struct PhoneBookEntry
		{
			std::string name;
			std::string phone;	
		};
		
		void AddEntry ( std::string name, std::string phoneNumber );
		void SlideInfoOut ( );
		void SlideInfoIn ( );
		
		MiniUI::Widgets::Widget* _pListing;
		MiniUI::Widgets::Widget* _pSlider;
		MiniUI::Widgets::Widget* _pName;
		MiniUI::Widgets::Widget* _pPhone;
		
		MiniUI::Widgets::Widget* _pOnShowAnimation;
		MiniUI::Widgets::Widget* _pOnHideAnimation;
		
		int _selectedIndex;
		bool _firstSelection;
		
		std::vector<PhoneBookEntry> _phoneBook;
	};
}

#endif // _APPLICATIONS_PHONEBOOK_H_
