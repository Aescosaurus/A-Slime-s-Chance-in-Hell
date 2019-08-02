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
}

void Campaign::Draw()
{
	map.Draw( gfx );
	player.Draw( gfx );
}
