#include "Demon.h"

Demon::Demon( const Vec2& pos )
	:
	coll( pos,radius )
{}

void Demon::Update( const Vec2& playerPos,const TorchHandler& torchHandler,float dt )
{
	retargetTimer.Update( dt );
	if( retargetTimer.IsDone() )
	{
		retargetTimer.Reset();
		vel = ( playerPos - coll.pos ).GetNormalized();
	}

	coll.pos += vel * moveSpeed * dt;

	canDraw = false;
	for( const auto& torch : torchHandler.GetTorches() )
	{
		if( coll.IsCollidingWith( Collider{ Vec2( torch.pos ) /
			TileMap::tileSize,float( torch.radius ) /
			TileMap::tileSize } ) )
		{
			canDraw = true;
		}
	}
}

void Demon::Draw( Graphics& gfx ) const
{
	if( canDraw )
	{
		coll.Draw( Colors::Red,gfx );
	}
}

void Demon::Cull()
{
	cull = true;
}

const Collider& Demon::GetColl() const
{
	return( coll );
}

bool Demon::WillCull() const
{
	return( cull );
}

bool Demon::IsVisible() const
{
	return( canDraw );
}
