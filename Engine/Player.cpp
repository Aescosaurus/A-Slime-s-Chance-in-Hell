#include "Player.h"

Player::Player( const TileMap& map )
	:
	coll( Vec2( map.GetPlayerSpawn() ),radius ),
	map( map )
{}

void Player::Update( float dt )
{
	auto& pos = coll.pos;

	vel.y += gravAcc * dt;

	vel *= velDecayRate;

	const auto moveInfo = coll.CanMove( map,vel * dt );

	if( moveInfo.x )
	{
		pos.x += vel.x * dt;
	}

	if( moveInfo.y )
	{
		pos.y += vel.y * dt;
		canJump = false;
	}
	else
	{
		vel.y = 0.0f;
		canJump = true;
	}
}

void Player::Draw( Graphics& gfx ) const
{
	coll.Draw( Colors::Blue,gfx );
}

void Player::Move( const Vec2& diff )
{
	vel.x += ( diff.x / 10.0f ) * speed;
}

void Player::HybridJump( const Vec2& diff )
{
	if( canJump )
	{
		// vel += ( diff / 5.0f ) * hybridJumpPower;
		vel.x += ( diff.x / 7.0f ) * hybridJumpPower;
		vel.y += ( diff.y / 5.0f ) * hybridJumpPower;
	}
}

const Collider& Player::GetColl() const
{
	return( coll );
}
