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
		radius( radius ),
		radiusSq( radius * radius )
	{}

	void Draw( Color c,Graphics& gfx ) const
	{
		gfx.DrawCircle( Vei2( pos * float( TileMap::tileSize ) ),
			int( radius * float( TileMap::tileSize ) ),c );
	}

	bool Contains( const Vec2& point ) const
	{
		return( ( point - pos ).GetLengthSq() < radiusSq );
	}
	Vec2b CanMove( const TileMap& map,
		const Vec2& testMove ) const
	{
		std::vector<Vec2> testPositions;
		testPositions.emplace_back( pos + Vec2::Up() * radius );
		testPositions.emplace_back( pos + Vec2::Down() * radius );
		testPositions.emplace_back( pos + Vec2::Left() * radius );
		testPositions.emplace_back( pos + Vec2::Right() * radius );
		testPositions.emplace_back( pos + Vec2{ 1,1 }.GetNormalized() * radius );
		testPositions.emplace_back( pos + Vec2{ -1,1 }.GetNormalized() * radius );
		testPositions.emplace_back( pos + Vec2{ 1,-1 }.GetNormalized() * radius );
		testPositions.emplace_back( pos + Vec2{ -1,-1 }.GetNormalized() * radius );

		bool xMoveValid = true;
		bool yMoveValid = true;
		for( const auto& pos : testPositions )
		{
			if( map.GetTile( int( pos.x + testMove.x ),int( pos.y ) ) !=
				TileMap::TileType::Air )
			{
				xMoveValid = false;
			}
			if( map.GetTile( int( pos.x ),int( pos.y + testMove.y ) ) !=
				TileMap::TileType::Air )
			{
				yMoveValid = false;
			}
		}

		return( Vec2b{ xMoveValid,yMoveValid } );
	}
public:
	Vec2 pos;
	float radius;
	float radiusSq;
};