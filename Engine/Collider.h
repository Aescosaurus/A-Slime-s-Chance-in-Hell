#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "TileMap.h"

class Collider
{
public:
	Collider( const Vec2& pos,float radius )
		:
		pos( pos ),
		radius( radius )
	{}

	void Draw( Color c,Graphics& gfx ) const
	{
		gfx.DrawCircle( Vei2( pos * float( TileMap::tileSize ) ),
			int( radius ),c );
	}
public:
	Vec2 pos;
	float radius;
};