#include "Demon.h"

Demon::Demon( const Vec2& pos )
	:
	coll( pos,radius )
{}

void Demon::Update( const Vec2& playerPos,float dt )
{
	const auto diff = ( playerPos - coll.pos ).GetNormalized();

	coll.pos += diff * moveSpeed * dt;
}

void Demon::Draw( Graphics& gfx ) const
{
	coll.Draw( Colors::Red,gfx );
}
