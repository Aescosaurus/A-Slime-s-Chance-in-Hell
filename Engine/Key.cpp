#include "Key.h"

Key::Key( const Vei2& pos )
	:
	coll( Vec2( pos ) + Vec2{ radius,radius },radius )
{}

void Key::Draw( Graphics& gfx ) const
{
	coll.Draw( Colors::Green,gfx );
}

const Collider& Key::GetColl() const
{
	return( coll );
}
