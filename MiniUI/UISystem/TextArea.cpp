#include "TextArea.h"
#include <MiniUI/Host/IRenderer.h>

using namespace std;
using namespace MiniUI::Graphics;

namespace MiniUI
{
	namespace UISystem
	{
		///////////////////////////////////////////////////////////////////////
		TextArea::TextArea ( )
		///////////////////////////////////////////////////////////////////////
		{
			_pRenderable = Host::HostIntegration::Renderer->CreateRenderable();
		}

		///////////////////////////////////////////////////////////////////////
		TextArea::~TextArea ( )
		///////////////////////////////////////////////////////////////////////
		{
			delete _pRenderable;
		}

		///////////////////////////////////////////////////////////////////////
		bool TextArea::BuildText ( string text, Font* pFont, bool wordWrap, int width )
		///////////////////////////////////////////////////////////////////////
		{
			_pRenderable->image = pFont->GetImageResource();
			_pRenderable->clear();

			if ( !wordWrap )
			{
				// Just draw out the text ignoring size
				int pos = 0;
				for ( int i = 0; i < text.length(); i++ )
				{
					GraphicalRect rect = pFont->GetCharacter ( text[i] );

					int width = rect.coordinates[2].position.x;

					for ( int j = 0; j < 4; j++ )
						rect.coordinates[j].position.x += pos;

					_pRenderable->push_back ( rect );
					pos += width;
				}
			}

			return true;
		}
	}

}
