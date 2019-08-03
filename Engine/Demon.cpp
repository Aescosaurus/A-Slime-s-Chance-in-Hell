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

void Demon::Draw( const TorchHandler& torchHandler,Graphics& gfx ) const
{
	bool canDraw = false;
	for( const auto& torch : torchHandler.GetTorches() )
	{
		if( coll.IsCollidingWith( Collider{ Vec2( torch.pos ) /
			TileMap::tileSize,float( torch.radius ) /
			TileMap::tileSize } ) )
		{
			canDraw = true;
		}
	}

	if( canDraw )
	{
		coll.Draw( Colors::Red,gfx );
	}
}
