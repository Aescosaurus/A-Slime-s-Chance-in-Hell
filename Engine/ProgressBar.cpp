#include "ProgressBar.h"

void ProgressBar::Draw( const Vei2& pos,float percent,
	Color c,const std::string& text,Graphics& gfx ) const
{
	if( percent > 0.0f )
	{
		gfx.DrawRectSafe( pos.x - width / 2,pos.y,
			int( float( width ) * percent ),height,c );

		luckyPixel->DrawTextCentered( text,
			pos + Vei2::Down() * 25,c,gfx );
	}
}
