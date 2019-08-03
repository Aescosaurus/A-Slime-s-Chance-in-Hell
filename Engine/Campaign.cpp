#include "Campaign.h"

Campaign::Campaign( Keyboard& kbd,Mouse& mouse,Graphics& gfx )
	:
	kbd( kbd ),
	mouse( mouse ),
	gfx( gfx ),
	player( map )
{
	for( const auto& pos : map.GetEnemySpawns() )
	{
		enemySpawners.emplace_back( EnemySpawner{ pos } );
	}
}

void Campaign::Update()
{
	auto dt = ft.Mark();
	if( dt > 0.5f ) dt = 0.0f; // 0.5s lag = :(

	player.Update( dt );

	const auto mousePos = Vec2( mouse.GetPos() );
	diff = ( mousePos / TileMap::tileSize ) -
		player.GetColl().pos;

	actionTimer.Update( dt );

	if( mouse.LeftIsPressed()/* && actionTimer.IsDone()*/ )
	{
		bool completedAction = false;

		actionTimer.Reset();

		if( player.GetColl().Contains( mousePos /
			TileMap::tileSize ) && !completedAction )
		{
			placingTorch = true;
			chargePower += chargeRate * dt;
			completedAction = true;
		}

		// if( !completedAction )
		// {
		// 	// check if mouse clicked on enemy
		// 	// if so player.shoot()
		// 	// if so completedAction = true;
		// }

		if( !completedAction )
		{
			chargePower += chargeRate * dt;
			jumping = true;
			if( chargePower >= 1.0f )
			{
				PlayerJump();
				jumping = false;
				completedAction = true;
			}
		}
	}
	else if( jumping )
	{
		PlayerJump();
		jumping = false;
	}
	if( chargePower > 1.0f && placingTorch )
	{
		torch.PlaceTorch( player.GetColl().pos );
		chargePower = 0.0f;
	}

	torch.Update( dt );

	for( auto& spawner : enemySpawners )
	{
		spawner.Update( player.GetColl().pos,dt );
	}
}

void Campaign::Draw()
{
	map.Draw( gfx );
	player.Draw( gfx );
	for( const auto& spawner : enemySpawners )
	{
		spawner.Draw( gfx );
	}


	torch.Draw( gfx );

	// gfx.DrawLine( player.GetColl().pos * TileMap::tileSize,
	// 	( player.GetColl().pos + ( diff * chargePower ) ) *
	// 	TileMap::tileSize,
	// 	Colors::White );
}

void Campaign::PlayerJump()
{
	player.HybridJump( diff.GetNormalized() *
		std::min( 1.0f,chargePower ) );
	chargePower = 0.0f;
}
