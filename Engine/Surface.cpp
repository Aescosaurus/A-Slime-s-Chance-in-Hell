#include "Surface.h"
#include "ChiliWin.h"
#include <cassert>
#include <fstream>
#include "Graphics.h"

Surface::Surface( int width,int height ) :
	width( width ),
	height( height ),
	pixels( width * height )
{}

Surface::Surface( const std::string& filename )
{
	std::ifstream file( filename,std::ios::binary );
	assert( file );

	BITMAPFILEHEADER bmFileHeader;
	file.read( reinterpret_cast< char* >( &bmFileHeader ),
		sizeof( bmFileHeader ) );

	BITMAPINFOHEADER bmInfoHeader;
	file.read( reinterpret_cast< char* >( &bmInfoHeader ),
		sizeof( bmInfoHeader ) );

	assert( bmInfoHeader.biBitCount == 24 ||
		bmInfoHeader.biBitCount == 32 );
	assert( bmInfoHeader.biCompression == BI_RGB );

	const bool is32b = bmInfoHeader.biBitCount == 32;

	width = bmInfoHeader.biWidth;

	// Test for reverse row order and
	//  control y loop accordingly.
	int yStart;
	int yEnd;
	int dy;
	if( bmInfoHeader.biHeight < 0 )
	{
		height = -bmInfoHeader.biHeight;
		yStart = 0;
		yEnd = height;
		dy = 1;
	}
	else
	{
		height = bmInfoHeader.biHeight;
		yStart = height - 1;
		yEnd = -1;
		dy = -1;
	}

	pixels.resize( width * height );

	file.seekg( bmFileHeader.bfOffBits );
	// Padding is for 24 bit depth only.
	const int padding = ( 4 - ( width * 3 ) % 4 ) % 4;

	for( int y = yStart; y != yEnd; y += dy )
	{
		for( int x = 0; x < width; ++x )
		{
			PutPixel( x,y,Color( file.get(),file.get(),file.get() ) );
			if( is32b )
			{
				file.seekg( 1,std::ios::cur );
			}
		}
		if( !is32b )
		{
			file.seekg( padding,std::ios::cur );
		}
	}

	*this = GetExpandedBy( Vei2{ 3,3 } );
}

Surface::Surface( const Surface& other,const RectI& clip )
{
	*this = other.GetClipped( clip );
}

Surface::Surface( const Surface& other,const Vei2& expandSize )
{
	*this = other.GetExpandedBy( expandSize );
}

Surface::Surface( const Surface& other,bool xFlipped,bool yFlipped )
{
	Surface guineaPig = { other.GetWidth(),other.GetHeight() };

	if( xFlipped ) guineaPig = other.GetXReversed();

	if( yFlipped ) guineaPig = guineaPig.GetYReversed();

	*this = guineaPig;
}

Surface::Surface( Surface&& donor )
{
	*this = std::move( donor );
}

Surface& Surface::operator=( Surface&& rhs )
{
	width = rhs.width;
	height = rhs.height;
	pixels = std::move( rhs.pixels );

	rhs.width = 0;
	rhs.height = 0;

	return( *this );
}

void Surface::PutPixel( int x,int y,Color c )
{
	assert( x >= 0 );
	assert( x < width );
	assert( y >= 0 );
	assert( y < height );
	pixels.data()[y * width + x] = c;
}

void Surface::DrawRect( int x,int y,int width,int height,Color c )
{
	for( int i = y; i < y + height; ++i )
	{
		for( int j = x; j < x + width; ++j )
		{
			PutPixel( j,i,c );
		}
	}
}

void Surface::DrawCircle( const Vei2& pos,int radius,Color c )
{
	const int radiusSq = radius * radius;
	for( int y = pos.y - radius; y < pos.y + radius; ++y )
	{
		for( int x = pos.x - radius; x < pos.x + radius; ++x )
		{
			const int xDiff = pos.x - x;
			const int yDiff = pos.y - y;
			if( x >= 0 && x < width &&
				y >= 0 && y < height &&
				xDiff * xDiff + yDiff * yDiff < radiusSq )
			{
				PutPixel( x,y,c );
			}
		}
	}
}

Color Surface::GetPixel( int x,int y ) const
{
	assert( x >= 0 );
	assert( x < width );
	assert( y >= 0 );
	assert( y < height );
	return pixels.data()[y * width + x];
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}

Vei2 Surface::GetSize() const
{
	return Vei2{ width,height };
}

RectI Surface::GetRect() const
{
	return{ 0,width,0,height };
}

Surface Surface::GetExpandedBy( const Vei2& amount ) const
{
	Surface bigger = { amount.x * GetWidth(),amount.y * GetHeight() };

	for( int y = 0; y < this->height; ++y )
	{
		for( int x = 0; x < this->width; ++x )
		{
			bigger.DrawRect( x * amount.x,y * amount.y,
				int( amount.x ),int( amount.y ),
				GetPixel( x,y ) );
		}
	}

	return( bigger );
}

Surface Surface::GetXReversed() const
{
	Surface flipped = Surface{ width,height };

	for( int y = 0; y < height; ++y )
	{
		int otherX = 0;
		// Loop in reverse x.
		for( int x = width - 1; x >= 0; --x )
		{
			flipped.PutPixel( otherX,y,GetPixel( x,y ) );
			++otherX;
		}
	}

	return( flipped );
}

Surface Surface::GetYReversed() const
{
	Surface flipped = Surface{ width,height };

	int otherY = 0;
	// Loop in reverse y.
	for( int y = height - 1; y >= 0; --y )
	{
		for( int x = width - 1; x >= 0; --x )
		{
			flipped.PutPixel( x,otherY,GetPixel( x,y ) );
		}
		++otherY;
	}

	return( flipped );
}

Surface Surface::GetClipped( const RectI& clip ) const
{
	Surface clipped = { clip.GetWidth(),clip.GetHeight() };

	int i = 0;
	int j = 0;
	for( int y = clip.top; y < clip.bottom; ++y )
	{
		for( int x = clip.left; x < clip.right; ++x )
		{
			clipped.PutPixel( j,i,GetPixel( x,y ) );
			++j;
		}
		j = 0;
		++i;
	}

	return( clipped );
}