#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Collider.h"

class Demon
{
public:
	Demon( const Vec2& pos );

	void Update( const Vec2& playerPos,float dt );
	void Draw( Graphics& gfx ) const;
private:
	static constexpr float radius = 0.8f;
	Collider coll;
	static constexpr float moveSpeed = 0.6f;
};