
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
	class Substitution
	{
	public:
		Substitution( Color c,Color s )
			:
			chroma( c ),
			sub( s )
		{}
		void operator()( Color cSrc,int xDest,int yDest,Graphics& gfx ) const
		{
			if( cSrc != chroma )
			{
				gfx.PutPixel( xDest,yDest,sub );
			}
		}
	private:
		Color chroma = Colors::Magenta;
		Color sub;
	};
	class SubstituteFade
	{
	public:
		SubstituteFade( Color chroma,Color sub,float fadeAmount )
			:
			chroma( chroma ),
			substitution( sub ),
			fadeAmount( fadeAmount )
		{}
		void operator()( Color cSrc,int xDest,int yDest,Graphics& gfx )
		{
			if( cSrc != chroma )
			{
				gfx.PutPixel( xDest,yDest,cSrc );
				gfx.PutPixelAlpha( xDest,yDest,substitution,fadeAmount );
			}
		}
	private:
		Color chroma;
		Color substitution;
		float fadeAmount;
	};
}