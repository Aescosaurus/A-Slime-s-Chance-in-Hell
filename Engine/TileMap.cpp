#include "TileMap.h"
#include <fstream>
#include <cassert>

TileMap::TileMap()
{
	tiles.resize( width * height ); // resize to create empty elements

	// LoadMap( "Levels/TestLevel.lvl" );
}

void TileMap::Draw( Graphics& gfx ) const
{
	for( int y = 0; y < height; ++y )
	{
		for( int x = 0; x < width; ++x )
		{
			const auto tile = GetTile( x,y );
			if( tile == TileType::Air )
			{
				gfx.DrawRect( x * tileSize,y * tileSize,
					tileSize,tileSize,Colors::Cyan );
			}
			else if( tile == TileType::Wall )
			{
				gfx.DrawRect( x * tileSize,y * tileSize,
					tileSize,tileSize,Colors::Gray );
			}
		}
	}
}

void TileMap::LoadMap( const std::string& src )
{
	std::ifstream in{ src };
	assert( in.good() );

	enemySpawns.clear();

	int i = 0;
	int x = 0;
	int y = 0;
	for( char c = in.get(); in.good(); c = in.get() )
	{
		if( c != '\n' )
		{
			++x;
			if( c == 'p' ) // player
			{
				playerSpawnPos = Vei2{ x,y };
				c = '0';
			}
			else if( c == 'e' ) // enemy spawner
			{
				enemySpawns.emplace_back( Vei2{ x,y } );
				c = '1';
			}
			else if( c == 'k' ) // key
			{
				keySpawns.emplace_back( Vei2{ x,y } );
				c = '0';
			}

			tiles[i] = TileType( c - '0' );
			++i;
		}
		else
		{
			x = 0;
			++y;
		}
	}
}

void TileMap::Reset()
{
	enemySpawns.clear();
	keySpawns.clear();
}

TileMap::TileType TileMap::GetTile( int x,int y ) const
{
	if( x < 0 ) x = 0;
	if( x >= width ) x = width - 1;
	if( y < 0 ) y = 0;
	if( y >= height ) y = height - 1;
	return( tiles[y * width + x] );
}

const Vei2& TileMap::GetPlayerSpawn() const
{
	return( playerSpawnPos );
}

const std::vector<Vei2>& TileMap::GetEnemySpawns() const
{
	return( enemySpawns );
}

const std::vector<Vei2>& TileMap::GetKeySpawns() const
{
	return( keySpawns );
}

