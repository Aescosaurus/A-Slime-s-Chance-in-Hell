#include "Bullet.h"

Bullet::Bullet( const Vec2& pos,const Vec2& target )
	:
	coll( pos,radius ),
	vel( ( target - pos ).GetNormalized() * moveSpeed )
{}

void Bullet::Update( float dt )
{
	coll.pos += vel * dt;
	
	// if offscreen dead = true;
}

void Bullet::Draw( Graphics& gfx ) const
{
	coll.Draw( Colors::Red,gfx );
}
