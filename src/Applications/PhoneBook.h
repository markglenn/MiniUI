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
	};
}

#endif // _APPLICATIONS_PHONEBOOK_H_
