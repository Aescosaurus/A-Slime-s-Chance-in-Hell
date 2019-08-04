#include "Demon.h"
#include "SpriteEffect.h"

Demon::Demon( const Vec2& pos )
	:
	coll( pos,radius ),
	anim( 0,0,30,30,4,*sprSheet,0.2f )
{
	anim.RandomizeCurFrame();
}

void Demon::Update( const Vec2& playerPos,const TorchHandler& torchHandler,float dt )
{
	anim.Update( dt );

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

void Demon::UpdateNoMove( const TorchHandler& torchHandler,float dt )
{
	anim.Update( dt );

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
		// coll.Draw( Colors::Red,gfx );

		anim.Draw( Vei2( coll.pos * float( TileMap::tileSize ) ),
			gfx,true,SpriteEffect::Chroma{} );
	}
}

void Demon::Cull()
{
	cull = true;
	ouchSound->Play();
}

void Demon::SetPos( const Vec2& pos )
{
	coll.pos = pos;
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
