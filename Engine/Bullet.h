#pragma once

#include "Collider.h"
#include "Codex.h"
#include "Animation.h"

class Bullet
{
public:
	Bullet( const Vec2& pos,const Vec2& target );
	
	void Update( const TileMap& map,float dt );
	void Draw( Graphics& gfx ) const;

	void Cull();

	bool WillCull() const;
	const Collider& GetColl() const;
private:
	static constexpr float radius = 0.3f;
	Collider coll;
	static constexpr float moveSpeed = 10.0f;
	Vec2 vel;
	bool cull = false;
	CSurfPtr sprSheet = SurfCodex::Fetch( "Images/Bullet.bmp" );
	Animation anim;
};