#include "Player.h"
#include "SpriteEffect.h"

Player::Player( const TileMap& map )
	:
	coll( Vec2( map.GetPlayerSpawn() ) + Vec2{ radius,radius },
		radius ),
	map( map ),
	idle( 0,0,30,30,4,*sprSheet,0.2f ),
	charge( 0,30,30,30,4,*sprSheet,0.2f ),
	jump( 0,30 * 2,30,30,4,*sprSheet,0.2f )
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
		if( action == State::Jump )
		{
			goIdleTimer.Update( dt );
			if( goIdleTimer.IsDone() )
			{
				goIdleTimer.Reset();
				SwitchAction( State::Idle );
			}
		}
		vel.x *= velDecayRate;
		vel.y = 0.0f;
		canJump = true;
	}

	switch( action )
	{
	case State::Idle:
		idle.Update( dt );
		break;
	case State::Charge:
		charge.Update( dt );
		break;
	case State::Jump:
		jump.Update( dt );
		break;
	}
}

void Player::Draw( Graphics& gfx ) const
{
	// coll.Draw( Colors::Blue,gfx );

	const auto drawPos = coll.pos * TileMap::tileSize;
	const auto effect = SpriteEffect::Chroma{};
	switch( action )
	{
	case State::Idle:
		idle.Draw( drawPos,gfx,true,effect );
		break;
	case State::Charge:
		charge.Draw( drawPos,gfx,true,effect );
		break;
	case State::Jump:
		jump.Draw( drawPos,gfx,true,effect );
		break;
	}
}

void Player::Move( const Vec2& diff )
{
	vel.x += diff.x * speed;
}

void Player::HybridJump( const Vec2& diff )
{
	coll.pos.y -= 0.2f;
	SwitchAction( State::Jump );
	if( canJump )
	{
		vel += diff * hybridJumpPower;
		// vel.x += ( diff.x / 7.0f ) * hybridJumpPower;
		// vel.y += ( diff.y / 5.0f ) * hybridJumpPower;
	}
}

void Player::Reset()
{
	coll.pos = Vec2( map.GetPlayerSpawn() ) +
		Vec2{ radius,radius };
	// Reset animations maybe?
}

void Player::ChargeJump()
{
	if( canJump ) SwitchAction( State::Charge );
}

void Player::Idlize()
{
	if( action == State::Charge ) SwitchAction( State::Idle );
}

const Collider& Player::GetColl() const
{
	return( coll );
}

void Player::SwitchAction( State state )
{
	switch( state )
	{
	case State::Idle:
		action = State::Idle;
		charge.Reset();
		jump.Reset();
		break;
	case State::Charge:
		action = State::Charge;
		idle.Reset();
		jump.Reset();
		break;
	case State::Jump:
		action = State::Jump;
		idle.Reset();
		charge.Reset();
		break;
	}
}
