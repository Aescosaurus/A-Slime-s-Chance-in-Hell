#include "Button.h"
#include "SpriteEffect.h"

Button::Button( const Surface& image,const Vei2& pos )
	:
	pos( pos ),
	image( image ),
	clickArea( pos,image.GetWidth(),image.GetHeight() )
{}

bool Button::Update( const Mouse& mouse )
{
	pressed = false;
	hovering = clickArea.ContainsPoint( mouse.GetPos() );
	clicking = mouse.LeftIsPressed();

	if( clicking )
	{
		if( canClick )
		{
			if( hovering ) pressed = true;
		}
		canClick = false;
	}
	else canClick = true;

	return( pressed );
}

void Button::Draw( Graphics& gfx ) const
{
	if( !hovering )
	{
		gfx.DrawSprite( pos.x,pos.y,image,false,
			SpriteEffect::Chroma{ Colors::Magenta } );
	}
	else
	{
		gfx.DrawSprite( pos.x,pos.y,image,false,
			SpriteEffect::SubstituteFade{ Colors::Magenta,
			Colors::White,0.5f } );
	}
}

const Vei2& Button::GetPos() const
{
	return( pos );
}

bool Button::IsHovering() const
{
	return( hovering );
}