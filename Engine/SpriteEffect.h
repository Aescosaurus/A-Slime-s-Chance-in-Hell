#pragma once

#include "Colors.h"
#include "Graphics.h"
#include <algorithm>

namespace SpriteEffect
{
	class PartialFade
	{
	public:
		PartialFade( float fade )
			:
			fade( fade )
		{}
		void operator()( Color cSrc,int xDest,int yDest,Graphics& gfx ) const
		{
			gfx.PutPixelAlpha( xDest,yDest,Colors::Black,std::max( 0.0f,
				fade - ( float( cSrc.GetR() ) / 255.0f ) ) );
		}
	private:
		float fade;
	};

	class Chroma
	{
	public:
		Chroma( Color chroma = Colors::Magenta )
			:
			chroma( chroma )
		{}
		void operator()( Color cSrc,int xDest,int yDest,Graphics& gfx ) const
		{
			if( cSrc != chroma )
			{
				gfx.PutPixel( xDest,yDest,cSrc );
			}
		}
	private:
		Color chroma;
	};

	class Copy
	{
	public:
		void operator()( Color cSrc,int xDest,int yDest,Graphics& gfx ) const
		{
			gfx.PutPixel( xDest,yDest,cSrc );
		}
	};
}