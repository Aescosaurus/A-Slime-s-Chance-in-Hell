#include "Bullet.h"
#include "SpriteEffect.h"

Bullet::Bullet( const Vec2& pos,const Vec2& target )
	:
	coll( pos,radius ),
	vel( ( target - pos ).GetNormalized() * moveSpeed ),
	anim( 0,0,30,30,4,*sprSheet,0.2f )
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

	anim.Update( dt );
}

void Bullet::Draw( Graphics& gfx ) const
{
	// coll.Draw( Colors::Red,gfx );

	anim.Draw( Vei2( coll.pos * TileMap::tileSize ),gfx,true,
		SpriteEffect::Chroma{} );
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
