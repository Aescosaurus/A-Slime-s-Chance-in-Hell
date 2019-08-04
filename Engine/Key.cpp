#include "Key.h"
#include "SpriteEffect.h"

Key::Key( const Vei2& pos )
	:
	coll( Vec2( pos ) + Vec2{ -radius,radius },radius ),
	anim( 0,0,30,30,4,*sprSheet,0.2f )
{
	anim.RandomizeCurFrame();
}

void Key::Update( const TorchHandler& torchHandler,float dt )
{
	if( !collected )
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
	else
	{
		vel.y += gravAcc * dt;
		coll.pos += vel * dt;
		if( coll.pos.y - coll.radius > float( Graphics::ScreenHeight ) )
		{
			cull = true;
		}
	}
}

void Key::Draw( Graphics& gfx ) const
{
	if( canDraw )
	{
		// coll.Draw( Colors::Yellow,gfx );

		anim.Draw( Vei2( coll.pos * float( TileMap::tileSize ) ),
			gfx,true,SpriteEffect::Chroma{} );
	}
}

void Key::Collect()
{
	collected = true;
	vel.y -= jumpPower;
	collectSound->Play();
}

void Key::StartCollect()
{
	if( !startedCollect )
	{
		startedCollect = true;
		keyCollectSound->Play();
	}
}

const Collider& Key::GetColl() const
{
	return( coll );
}

bool Key::IsVisible() const
{
	return( canDraw );
}

bool Key::WillCull() const
{
	return( cull );
}
