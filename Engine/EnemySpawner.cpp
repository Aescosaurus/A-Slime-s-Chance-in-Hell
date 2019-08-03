#include "EnemySpawner.h"
#include "Random.h"

void EnemySpawner::Update( const Vec2& playerPos,float dt )
{
	demonSpawnTimer.Update( dt );
	if( demonSpawnTimer.IsDone() )
	{
		demonSpawnTimer.Reset();

		demons.emplace_back( Demon{ Vec2( spawnPosList[
			int( Random{ 0,int( spawnPosList.size() - 1 ) } )] ) } );
	}

	for( auto& demon : demons )
	{
		demon.Update( playerPos,dt );
	}
}

void EnemySpawner::Draw( const TorchHandler& torchHandler,Graphics& gfx ) const
{
	for( const auto& demon : demons )
	{
		demon.Draw( torchHandler,gfx );
	}
}

void EnemySpawner::AddPos( const Vei2& pos )
{
	spawnPosList.emplace_back( pos );
}

const std::vector<Demon>& EnemySpawner::GetEnemies() const
{
	return( demons );
}
