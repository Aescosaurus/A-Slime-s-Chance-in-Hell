#include "Campaign.h"
#include <cassert>
#include "ChiliUtils.h"
#include <functional>
#include "SpriteEffect.h"

Campaign::Campaign( Keyboard& kbd,Mouse& mouse,Graphics& gfx )
	:
	kbd( kbd ),
	mouse( mouse ),
	gfx( gfx ),
	player( map )
{
	LoadNextLevel();
}

// void Campaign::Update()
// {
// 	auto dt = ft.Mark();
// 	if( dt > 0.5f ) dt = 0.0f; // 0.5s lag = :(
// 
// 	player.Update( dt );
// 
// 	const auto mousePos = Vec2( mouse.GetPos() );
// 	diff = ( mousePos / TileMap::tileSize ) -
// 		player.GetColl().pos;
// 
// 	actionTimer.Update( dt );
// 
// 	if( mouse.LeftIsPressed()/* && actionTimer.IsDone()*/ )
// 	{
// 		bool completedAction = false;
// 
// 		actionTimer.Reset();
// 
// 		if( player.GetColl().Contains( mousePos /
// 			TileMap::tileSize ) && !completedAction )
// 		{
// 			placingTorch = true;
// 			chargePower += chargeRate * dt;
// 			completedAction = true;
// 		}
// 
// 		if( !completedAction )
// 		{
// 			hoveringEnemy = false;
// 			for( const auto& demon : enemySpawner.GetEnemies() )
// 			{
// 				if( demon.GetColl().Contains( mousePos / TileMap::tileSize ) )
// 				{
// 					hoveringEnemy = true;
// 					chargePower += chargeRate * dt;
// 					completedAction = true;
// 				}
// 			}
// 			// check if mouse clicked on enemy
// 			// if so player.shoot()
// 			// if so completedAction = true;
// 		}
// 
// 		if( !completedAction )
// 		{
// 			chargePower += chargeRate * dt;
// 			jumping = true;
// 			if( chargePower >= 1.0f )
// 			{
// 				PlayerJump();
// 				jumping = false;
// 				completedAction = true;
// 			}
// 		}
// 	}
// 
// 	if( jumping )
// 	{
// 		PlayerJump();
// 		jumping = false;
// 	}
// 
// 	if( chargePower > 1.0f && placingTorch )
// 	{
// 		torchHandler.PlaceTorch( player.GetColl().pos );
// 		chargePower = 0.0f;
// 	}
// 
// 	if( chargePower > 1.0f && hoveringEnemy )
// 	{
// 		bullets.emplace_back( Bullet{ player.GetColl().pos,mousePos } );
// 		chargePower = 0.0f;
// 	}
// 
// 	torchHandler.Update( dt );
// 
// 	enemySpawner.Update( player.GetColl().pos,dt );
// 
// 	for( auto& bullet : bullets )
// 	{
// 		bullet.Update( dt );
// 	}
// }

void Campaign::Update2()
{
	auto dt = ft.Mark();
	if( dt > 0.5f ) dt = 0.0f; // 0.5s lag = :(

	player.Update( dt );

	torchHandler.Update( dt );

	enemySpawner.Update( player.GetColl().pos,torchHandler,dt );

	for( auto& bullet : bullets )
	{
		bullet.Update( map,dt );

		for( auto& enemy : enemySpawner.GetEnemies() )
		{
			if( enemy.GetColl().IsCollidingWith( bullet.GetColl() ) )
			{
				enemy.Cull();
				bullet.Cull();
			}
		}
	}

	for( auto& key : keys )
	{
		key.Update( torchHandler,dt );
	}

	chili::remove_erase_if( bullets,std::mem_fn( &Bullet::WillCull ) );
	chili::remove_erase_if( enemySpawner.GetEnemies(),std::mem_fn( &Demon::WillCull ) );

	{
		const auto& enemies = enemySpawner.GetEnemies();
		bool collidedEnemy = false;
		for( int i = 0; i < int( enemies.size() ); ++i )
		{
			if( player.GetColl().IsCollidingWith(
				enemies[i].GetColl() ) )
			{
				deathTimer.Update( dt );
				collidedEnemy = true;
			}
		}
		if( !collidedEnemy ) deathTimer.Reset();
		if( deathTimer.IsDone() )
		{
			--curLevel;
			LoadNextLevel();
		}
	}

	const auto mousePos = Vec2( mouse.GetPos() ) / TileMap::tileSize;

	if( mouse.LeftIsPressed() )
	{
		if( curAction == ActionType::None )
		{
			for( const auto& demon : enemySpawner.GetEnemies() )
			{
				if( demon.GetColl().Contains( mousePos ) &&
					demon.IsVisible() )
				{
					startAction.Update( dt );
					if( testAction != ActionType::Attack )
					{
						startAction.Reset();
					}
					if( startAction.IsDone() )
					{
						startAction.Reset();
						curAction = ActionType::Attack;
					}
					testAction = ActionType::Attack;
					return;
				}
			}

			for( int i = 0; i < int( keys.size() ); ++i )
			{
				const auto& key = keys[i];

				const auto dist = ( key.GetColl().pos -
					player.GetColl().pos ).GetLengthSq();

				if( dist < keyCollectDist * keyCollectDist &&
					key.GetColl().Contains( mousePos ) &&
					key.IsVisible() )
				{
					startAction.Update( dt );
					if( testAction != ActionType::CollectKey )
					{
						startAction.Reset();
					}
					if( startAction.IsDone() )
					{
						startAction.Reset();
						selectedKey = i;
						curAction = ActionType::CollectKey;
					}
					testAction = ActionType::CollectKey;
					return;
				}
			}

			if( player.GetColl().Contains( mousePos ) )
			{
				startAction.Update( dt );
				if( testAction != ActionType::PlaceTorch )
				{
					startAction.Reset();
				}
				if( startAction.IsDone() )
				{
					startAction.Reset();
					curAction = ActionType::PlaceTorch;
				}
				testAction = ActionType::PlaceTorch;
				return;
			}

			const auto diff = mousePos - player.GetColl().pos;
			if( std::abs( diff.x ) > std::abs( diff.y ) )
			{
				startAction.Update( dt );
				if( testAction != ActionType::Move )
				{
					startAction.Reset();
				}
				if( startAction.IsDone() )
				{
					startAction.Reset();
					curAction = ActionType::Move;
				}
				testAction = ActionType::Move;
				return;
			}
			else
			{
				startAction.Update( dt );
				if( testAction != ActionType::Jump )
				{
					startAction.Reset();
				}
				if( startAction.IsDone() )
				{
					startAction.Reset();
					curAction = ActionType::Jump;
				}
				testAction = ActionType::Jump;
				return;
			}
		}

		if( curAction != ActionType::None &&
			testAction != ActionType::None )
		{
			chargeTimer.Update( dt );
		}
	}
	else
	{
		chargeTimer.Reset();
		curAction = ActionType::None;
		testAction = ActionType::None;
	}

	if( chargeTimer.IsDone() )
	{
		const auto diff = mousePos - player.GetColl().pos;

		switch( curAction )
		{
		case ActionType::Move:
			player.HybridJump( diff.GetNormalized() *
				chargeTimer.GetPercent() );
			break;
		case ActionType::Jump:
			player.HybridJump( diff.GetNormalized() *
				chargeTimer.GetPercent() );
			break;
		case ActionType::CollectKey:
			assert( selectedKey != -1 );
			chili::remove_element( keys,selectedKey );
			selectedKey = -1;
			// Play animation for collecting key.
			if( keys.size() == 0 )
			{
				LoadNextLevel();
			}
			break;
		case ActionType::PlaceTorch:
			torchHandler.PlaceTorch( player.GetColl().pos );
			break;
		case ActionType::Attack:
			bullets.emplace_back( Bullet{
				player.GetColl().pos,mousePos } );
			break;
		default:
			assert( false );
			break;
		}

		curAction = ActionType::None;
		testAction = ActionType::None;
		chargeTimer.Reset();
	}
}

void Campaign::Draw()
{
	gfx.DrawSprite( 0,0,background,false,SpriteEffect::Copy{} );
	map.Draw( gfx );
	player.Draw( gfx );
	for( const auto& key : keys ) key.Draw( gfx );
	enemySpawner.Draw( gfx );
	for( const auto& bullet : bullets ) bullet.Draw( gfx );

	torchHandler.Draw( gfx );

	// gfx.DrawLine( player.GetColl().pos * TileMap::tileSize,
	// 	( player.GetColl().pos + ( diff * chargePower ) ) *
	// 	TileMap::tileSize,
	// 	Colors::White );
}

void Campaign::LoadNextLevel()
{
	curAction = ActionType::None;
	testAction = ActionType::None;
	startAction.Reset();
	chargeTimer.Reset();

	map.Reset();
	torchHandler.Reset();
	enemySpawner.Reset();
	bullets.clear();
	keys.clear();
	selectedKey = -1;

	++curLevel;

	const std::string nextLevelName = "Levels/Level" +
		std::to_string( curLevel ) + ".lvl";

	map.LoadMap( nextLevelName );

	for( const auto& pos : map.GetEnemySpawns() )
	{
		enemySpawner.AddPos( pos );
	}

	for( const auto& pos : map.GetKeySpawns() )
	{
		keys.emplace_back( Key{ pos } );
	}

	player.Reset();
	torchHandler.PlaceTorch( player.GetColl().pos );
}

// void Campaign::PlayerJump()
// {
// 	player.HybridJump( diff.GetNormalized() *
// 		std::min( 1.0f,chargePower ) );
// 	chargePower = 0.0f;
// }
