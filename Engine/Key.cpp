#include "Key.h"

Key::Key( const Vei2& pos )
	:
	coll( Vec2( pos ) + Vec2{ radius,radius },radius )
{}

void Key::Update( const TorchHandler& torchHandler,float dt )
{
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
		coll.Draw( Colors::Yellow,gfx );
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
