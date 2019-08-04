#include "Menu.h"
#include "SpriteEffect.h"

void Menu::Update( const Mouse& mouse )
{
	pressedStart = start.Update( mouse );
}

void Menu::Draw( Graphics& gfx ) const
{
	gfx.DrawSprite( 0,0,*bg,false,SpriteEffect::Copy{} );

	start.Draw( gfx );
}

bool Menu::PressedStart() const
{
	return( pressedStart );
}
