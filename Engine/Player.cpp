#include "Player.h"

Player::Player( const TileMap& map )
	:
	coll( Vec2( map.GetPlayerSpawn() ),size )
{}

void Player::Draw( Graphics& gfx ) const
{
	coll.Draw( Colors::Blue,gfx );
}
