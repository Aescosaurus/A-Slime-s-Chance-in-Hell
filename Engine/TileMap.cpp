#include "TileMap.h"
#include <fstream>
#include <cassert>
#include "SpriteEffect.h"
#include "Random.h"

TileMap::TileMap()
{
	tiles.resize( width * height ); // resize to create empty elements

	// LoadMap( "Levels/TestLevel.lvl" );

	const Surface temp{ "Images/Walls.bmp" };
	for( int y = 0; y < temp.GetHeight() / tileSize; ++y )
	{
		for( int x = 0; x < temp.GetWidth() / tileSize; ++x )
		{
			wallSprs.emplace_back( temp.GetClipped( RectI{
				Vei2{ x,y } * tileSize,
				tileSize,tileSize } ) );
		}
	}
}

void TileMap::Draw( Graphics& gfx ) const
{
	for( int y = 0; y < height; ++y )
	{
		for( int x = 0; x < width; ++x )
		{
			const auto tile = GetTile( x,y );
			// if( tile == TileType::Air )
			// {
			// 	gfx.DrawRect( x * tileSize,y * tileSize,
			// 		tileSize,tileSize,Colors::Cyan );
			// }
			// else if( tile == TileType::Wall )
			// {
			// 	gfx.DrawRect( x * tileSize,y * tileSize,
			// 		tileSize,tileSize,Colors::Gray );
			// }
			
			if( tile != TileType::Air )
			{
				gfx.DrawSprite( x * tileSize,y * tileSize,
					wallSprs[int( tile ) - 1],false,
					SpriteEffect::Chroma{} );
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
			else if( c == 'd' ) // demon
			{
				enemySpawns.emplace_back( Vei2{ x,y } );
				c = '0';
			}

			if( c == '1' ) c = char( int( Random{ 1,4 } ) ) + '0';

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

