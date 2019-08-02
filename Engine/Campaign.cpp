#include "Campaign.h"

Campaign::Campaign( Keyboard& kbd,Mouse& mouse,Graphics& gfx )
	:
	kbd( kbd ),
	mouse( mouse ),
	gfx( gfx ),
	player( map )
{}

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
			// torch.light()
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
			if( chargePower >= 1.0f )
			{
				PlayerJump();
				completedAction = true;
			}
		}
	}
	else if( chargePower > 0.0f )
	{
		PlayerJump();
	}
}

void Campaign::Draw()
{
	map.Draw( gfx );
	player.Draw( gfx );

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
