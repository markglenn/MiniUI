#include "EventArea.h"

using namespace MiniUI::Input;
namespace MiniUI
{
	namespace Widgets
	{
		///////////////////////////////////////////////////////////
		EventArea::EventArea ( )
			: IsMouseOver ( 0 ), IsMouseDown ( 0 )
		///////////////////////////////////////////////////////////
		{
		}

		///////////////////////////////////////////////////////////
		EventArea::~EventArea ( )
		///////////////////////////////////////////////////////////
		{
		}

		///////////////////////////////////////////////////////////
		void EventArea::HandleMouse ( int x, int y, Mouse* pMouse )
		///////////////////////////////////////////////////////////
		{	
			if ( area.PointInRectangle ( x, y ) )
			{
				if ( !IsMouseOver )
					this->OnMouseOver();
				else
					this->OnMouseHover ( x, y );

				IsMouseOver = true;

				if ( !IsMouseDown && pMouse->leftMouseDown )
				{
					this->OnMouseDown ( x, y );
					IsMouseDown = true;
				}
			}
			else
			{
				if ( IsMouseOver )
					this->OnMouseOut ( );

				IsMouseOver = false;
			}

			if ( IsMouseDown )
			{
				if ( !pMouse->leftMouseDown )
				{
					this->OnMouseUp ( );
					IsMouseDown = false;
				}
				else
					this->OnMouseMove ( x, y );
			}


		}
	}

}
