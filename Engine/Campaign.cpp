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

	actionTimer.Update( dt );

	if( mouse.LeftIsPressed() && actionTimer.IsDone() )
	{
		const auto mousePos = Vec2( mouse.GetPos() );
		const auto diff = ( mousePos / TileMap::tileSize ) -
			player.GetColl().pos;
		bool completedAction = false;

		actionTimer.Reset();

		if( player.GetColl().Contains( mousePos ) && !completedAction )
		{
			// player.Update( ActionType::Light,diff,dt );
			// torch.light()
			completedAction = true;
		}

		// if( !completedAction )
		// {
		// 	// check if mouse clicked on enemy
		// 	// if so player.shoot()
		// 	completedAction = true;
		// }

		if( !completedAction )
		{
			// if( std::abs( diff.x ) > std::abs( diff.y ) )
			// {
			// 	player.Move( diff );
			// }
			// else // y diff is greater
			// {
			// 	player.HybridJump( diff );
			// }
			player.HybridJump( diff );
			completedAction = true;
		}
	}
}

void Campaign::Draw()
{
	map.Draw( gfx );
	player.Draw( gfx );
}
