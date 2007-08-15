#include "TextArea.h"
#include <MiniUI/Host/IRenderer.h>
#include <MiniUI/Types/Integer.h>
#include <MiniUI/TinyXPath/xpath_static.h>

using namespace std;
using namespace MiniUI::Graphics;
using namespace MiniUI::TinyXPath;
using namespace MiniUI::Types;
using namespace MiniUI::UISystem;

namespace MiniUI
{
	namespace Widgets
	{
		///////////////////////////////////////////////////////////////////////
		TextArea::TextArea ( )
		///////////////////////////////////////////////////////////////////////
		{
			printf ("Created\n");
		}

		///////////////////////////////////////////////////////////////////////
		TextArea::~TextArea ( )
		///////////////////////////////////////////////////////////////////////
		{
		}

		///////////////////////////////////////////////////////////////////////
		bool TextArea::BuildText ( string text, Font* pFont, bool wordWrap, int width )
		///////////////////////////////////////////////////////////////////////
		{
			Renderable* pRenderable = this->GetRenderable();
			pRenderable->image = pFont->GetImageResource();
			pRenderable->clear();
			
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

					this->GetRenderable()->push_back ( rect );
					pos += width;
				}
			}

			return true;
		}
		
		///////////////////////////////////////////////////////////////////////
		void TextArea::OnLoad ( TiXmlElement *pSkin, TiXmlElement *pLayout )
		///////////////////////////////////////////////////////////////////////
		{
			Font *pFont = Font::GetFont( pLayout->Attribute ( "font" ) );
			std::string text = pLayout->Attribute ( "text" );
			
			o_xpath_int ( pLayout, "@x", this->GetRenderable()->position.x );
			o_xpath_int ( pLayout, "@y", this->GetRenderable()->position.y );
			
			BuildText ( text, pFont );
		}
	}

}
