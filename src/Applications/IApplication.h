#ifndef _APPLICATIONS_IAPPLICATION_H_
#define _APPLICATIONS_IAPPLICATION_H_

#include <MiniUI/UIManager.h>
#include <string>

namespace Applications
{
	class IApplication
	{
	public:
		IApplication ( MiniUI::UIManager *pManager );
		virtual ~IApplication ( );
		
		void Show ( );
		void Hide ( );
		
		virtual void OnShow ( ) { }
		virtual void OnHide ( ) { }
		
		virtual void OnEvent ( MiniUI::UIEvent* pEvent ) = 0;
		
		MiniUI::UIManager* UIManager() const { return _pManager; }

	protected:
	
	private:
		void OnUIEvent ( MiniUI::EventSystem::Event *pEvent );					
	
		MiniUI::UIManager* _pManager;
		MiniUI::EventSystem::Functor<IApplication> *_pEventFunctor;
	};
}

#endif // _APPLICATIONS_IAPPLICATION_H_
