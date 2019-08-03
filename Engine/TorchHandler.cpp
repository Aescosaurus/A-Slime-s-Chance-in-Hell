#include "TorchHandler.h"
#include "SpriteEffect.h"
#include "TileMap.h"
#include "ChiliUtils.h"
#include "TorchHandler.h"

TorchHandler::TorchHandler()
	:
	overlay( Graphics::ScreenWidth,Graphics::ScreenHeight )
{
	overlay.DrawRect( 0,0,
		overlay.GetWidth(),overlay.GetHeight(),
		Colors::Black );
}

void TorchHandler::Update( float dt )
{
	overlay.DrawRect( 0,0,
		overlay.GetWidth(),overlay.GetHeight(),
		Colors::Black );

	for( auto it = torches.begin(); it != torches.end(); ++it )
	{
		it->burnoutTimer.Update( dt );

		const auto col = 255 - int( it->burnoutTimer.GetPercent() * 255.0f );
		overlay.DrawCircle( it->pos,it->radius,
			Colors::MakeRGB( col,col,col ) );
	}

	chili::remove_erase_if( torches,[]( const TorchItem& torch )
	{
		return( torch.burnoutTimer.IsDone() );
	} );
}

void TorchHandler::Draw( Graphics& gfx ) const
{
	gfx.DrawSprite( 0,0,overlay,
		SpriteEffect::PartialFade{ globalOpacity } );
}

void TorchHandler::PlaceTorch( const Vec2& pos )
{
	TorchItem temp;
	temp.pos = Vei2( pos ) * TileMap::tileSize;

	torches.emplace_back( temp );
}

const std::vector<TorchHandler::TorchItem>& TorchHandler::GetTorches() const
{
	return( torches );
}
