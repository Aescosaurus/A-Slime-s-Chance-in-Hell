#pragma once

#include "Collider.h"

class Bullet
{
public:
	Bullet( const Vec2& pos,const Vec2& target );
	
	void Update( float dt );
	void Draw( Graphics& gfx ) const;
private:
	static constexpr float radius = 0.3f;
	Collider coll;
	static constexpr float moveSpeed = 10.0f;
	Vec2 vel;
};