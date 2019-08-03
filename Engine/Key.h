#pragma once

#include "Graphics.h"
#include "Collider.h"

class Key
{
public:
	Key( const Vei2& pos );

	void Draw( Graphics& gfx ) const;

	const Collider& GetColl() const;
private:
	static constexpr float radius = 0.4f;
	Collider coll;
};