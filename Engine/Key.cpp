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

void Key::Draw( Graphics& gfx ) const
{
	if( canDraw )
	{
		// coll.Draw( Colors::Yellow,gfx );

		anim.Draw( Vei2( coll.pos * float( TileMap::tileSize ) ),
			gfx,true,SpriteEffect::Chroma{} );
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
