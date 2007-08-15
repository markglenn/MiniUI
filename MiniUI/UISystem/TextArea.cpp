#include "TextArea.h"
#include <MiniUI/Host/IRenderer.h>
#include <MiniUI/Types/Integer.h>

using namespace std;
using namespace MiniUI::Graphics;
using namespace MiniUI::TinyXPath;
using namespace MiniUI::Types;

namespace MiniUI
{
	namespace UISystem
	{
		///////////////////////////////////////////////////////////////////////
		TextArea::TextArea ( )
		///////////////////////////////////////////////////////////////////////
		{
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
			
			this->GetRenderable()->image = pFont->GetImageResource();
			this->GetRenderable()->clear();
			
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
			
			BuildText ( text, pFont );
			
			this->GetRenderable()->position.x = Integer::ParseInt ( pLayout->Attribute ("x") );
			this->GetRenderable()->position.y = Integer::ParseInt ( pLayout->Attribute ("y") );
			
		}
	}

}
