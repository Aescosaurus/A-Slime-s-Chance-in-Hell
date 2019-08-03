#include "EnemySpawner.h"

EnemySpawner::EnemySpawner( const Vei2& pos )
	:
	pos( pos )
{}

void EnemySpawner::Update( const Vec2& playerPos,float dt )
{
	demonSpawnTimer.Update( dt );
	if( demonSpawnTimer.IsDone() )
	{
		demonSpawnTimer.Reset();

		demons.emplace_back( Demon{ Vec2( pos ) } );
	}

	for( auto& demon : demons )
	{
		demon.Update( playerPos,dt );
	}
}

void EnemySpawner::Draw( Graphics& gfx ) const
{
	for( const auto& demon : demons )
	{
		demon.Draw( gfx );
	}
}
