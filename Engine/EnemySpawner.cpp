#include "EnemySpawner.h"
#include "Random.h"

void EnemySpawner::Update( const Vec2& playerPos,const TorchHandler& torchHandler,float dt )
{
	// demonSpawnTimer.Update( dt );
	// if( demonSpawnTimer.IsDone() )
	// {
	// 	demonSpawnTimer.Reset();
	// 
	// 	demons.emplace_back( Demon{ Vec2( spawnPosList[
	// 		int( Random{ 0,int( spawnPosList.size() - 1 ) } )] ) } );
	// }
	waveSpawnTimer.Update( dt );
	if( waveSpawnTimer.IsDone() )
	{
		enemySpawnTimer.Update( dt );
		if( enemySpawnTimer.IsDone() )
		{
			enemySpawnTimer.Reset();
			++curWaveEnemy;

			enemySpawnSound->Play( 1.5f );
			demons.emplace_back( Demon{ Vec2( spawnPosList[
				int( Random{ 0,int( spawnPosList.size() - 1 ) } )] ) } );

			if( curWaveEnemy >= enemiesPerWave )
			{
				curWaveEnemy = 0;
				waveSpawnTimer.Reset();
			}
		}
	}

	for( auto& demon : demons )
	{
		demon.Update( playerPos,torchHandler,dt );
	}
}

void EnemySpawner::Draw( Graphics& gfx ) const
{
	for( const auto& demon : demons )
	{
		demon.Draw( gfx );
	}
}

void EnemySpawner::AddPos( const Vei2& pos )
{
	spawnPosList.emplace_back( pos );
}

void EnemySpawner::Reset()
{
	spawnPosList.clear();
	demons.clear();
	// demonSpawnTimer.Reset();
	waveSpawnTimer.Reset();
	enemySpawnTimer.Reset();
}

std::vector<Demon>& EnemySpawner::GetEnemies()
{
	return( demons );
}
