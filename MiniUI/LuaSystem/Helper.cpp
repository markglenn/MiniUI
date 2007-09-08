#include "Helper.h"
#include <MiniUI/Widgets/WidgetFactory.h>
#include <MiniUI/Host/IRenderer.h>
#include <MiniUI/Host/HostIntegration.h>

using namespace luabind;
using namespace std;
using namespace MiniUI::Widgets;
using namespace MiniUI::Host;

namespace MiniUI
{
	namespace LuaSystem
	{
		///////////////////////////////////////////////////////////////////////
		Widget * Helper::CreateWidget ( std::string widget )
		///////////////////////////////////////////////////////////////////////
		{
			WidgetFactory widgetFactory;
			
			Widget *pWidget = widgetFactory.Create ( widget );
			pWidget->SetName ( widget );
			
			pWidget->SetRenderable ( HostIntegration::Renderer->CreateRenderable ( ) );
			
			return pWidget;
		}
		
		///////////////////////////////////////////////////////////////////////
		void Helper::RegisterWithLua ( LuaSystem::LuaVirtualMachine* pVM )
		///////////////////////////////////////////////////////////////////////
		{
			module(*pVM, "MiniUI")
			[
				def("CreateWidget", &Helper::CreateWidget)
			];
		}
	}

}
