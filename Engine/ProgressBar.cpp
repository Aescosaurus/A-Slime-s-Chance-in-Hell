#include "ProgressBar.h"

void ProgressBar::Draw( const Vei2& pos,float percent,
	Color c,const std::string& text,Graphics& gfx ) const
{
	gfx.DrawRectSafe( pos.x - width / 2,pos.y,
		int( float( width ) * percent ),height,c );
}
