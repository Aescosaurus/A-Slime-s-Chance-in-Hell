#pragma once

#include <vector>
#include <string>
#include "Graphics.h"
#include "Vec2.h"

class TileMap
{
public:
	enum class TileType
	{
		Air = 0,
		Wall
	};
public:
	TileMap();

	void Draw( Graphics& gfx ) const;

	void LoadMap( const std::string& src );

	TileType GetTile( int x,int y ) const;
	const Vei2& GetPlayerSpawn() const;
public:
	static constexpr int tileSize = 30;
	static constexpr int width = Graphics::ScreenWidth / tileSize; // 32
	static constexpr int height = Graphics::ScreenHeight / tileSize; // 18
private:
	std::vector<TileType> tiles;
	Vei2 playerSpawnPos;
};