#include "Bullet.h"

Bullet::Bullet( const Vec2& pos,const Vec2& target )
	:
	coll( pos,radius ),
	vel( ( target - pos ).GetNormalized() * moveSpeed )
{}

void Bullet::Update( const TileMap& map,float dt )
{
	auto& pos = coll.pos;

	pos += vel * dt;

	if( map.GetTile( int( pos.x ),int( pos.y ) ) !=
		TileMap::TileType::Air )
	{
		cull = true;
	}
}

void Bullet::Draw( Graphics& gfx ) const
{
	coll.Draw( Colors::Red,gfx );
}

void Bullet::Cull()
{
	cull = true;
}

bool Bullet::WillCull() const
{
	return( cull );
}

const Collider& Bullet::GetColl() const
{
	return( coll );
}
