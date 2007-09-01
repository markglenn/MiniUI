#include "Image.h"
#include <MiniUI/Host/IRenderer.h>
#include <MiniUI/Types/Integer.h>
#include <MiniUI/TinyXPath/xpath_static.h>
#include <MiniUI/Graphics/TextureManager.h>

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
		Image::Image ( )
		///////////////////////////////////////////////////////////////////////
		{
		}

		///////////////////////////////////////////////////////////////////////
		Image::~Image ( )
		///////////////////////////////////////////////////////////////////////
		{
		}

		///////////////////////////////////////////////////////////////////////
		void Image::OnLoad ( TiXmlElement *pSkin, TiXmlElement *pLayout )
		///////////////////////////////////////////////////////////////////////
		{
			if ( !pLayout->Attribute ("src") )
			{
				printf ( "Image tags require 'src' attribute\n");
				return;
			}
			if ( !pLayout->Attribute ("width") )
			{
				printf ( "Image tags require 'src' attribute\n");
				return;
			}
			if ( !pLayout->Attribute ("height") )
			{
				printf ( "Image tags require 'src' attribute\n");
				return;
			}
			
			int width = Integer::ParseInt ( pLayout->Attribute ( "width" ) );
			int height = Integer::ParseInt ( pLayout->Attribute ( "height" ) );
			
			// Load the image
			GetRenderable()->image = 
				TextureManager::Instance()->LoadImage ( pLayout->Attribute ("src") );
			
			// Create the graphical rect
			GraphicalRect rect;
			rect.coordinates[0].position.x = 0;
			rect.coordinates[0].position.y = 0;
			rect.coordinates[0].texture.x = 0.0;
			rect.coordinates[0].texture.y = 0.0;
			
			rect.coordinates[1].position.x = 0;
			rect.coordinates[1].position.y = height;
			rect.coordinates[1].texture.x = 00;
			rect.coordinates[1].texture.y = 1.0;

			rect.coordinates[2].position.x = width;
			rect.coordinates[2].position.y = height;
			rect.coordinates[2].texture.x = 1.0;
			rect.coordinates[2].texture.y = 1.0;

			rect.coordinates[3].position.x = width;
			rect.coordinates[3].position.y = 0;
			rect.coordinates[3].texture.x = 1.0;
			rect.coordinates[3].texture.y = 0.0;
			
			rect.isVisible = true;
			rect.id = "mainRect";
			
			GetRenderable()->push_back ( rect );
			GetRenderable()->size.x = width;
			GetRenderable()->size.y = height;

		}
	}

}
