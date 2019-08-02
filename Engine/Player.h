#pragma once

#include "Vec2.h"
#include "TileMap.h"
#include "Graphics.h"
#include "Collider.h"

class Player
{
public:
	Player( const TileMap& map );

	void Update( const TileMap& map );
	void Draw( Graphics& gfx ) const;
private:
	static constexpr float size = float( TileMap::tileSize ) / 2.0f;
	Collider coll;
};