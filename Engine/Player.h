#pragma once

#include "Vec2.h"
#include "TileMap.h"
#include "Graphics.h"
#include "Collider.h"
#include "ActionType.h"

class Player
{
public:
	Player( const TileMap& map );

	void Update( float dt );
	void Draw( Graphics& gfx ) const;

	void Move( const Vec2& diff );
	// void Jump( const Vec2& diff );
	void HybridJump( const Vec2& diff );
	// void Shoot( const Vec2& diff );

	const Collider& GetColl() const;
private:
	// static constexpr float size = float( TileMap::tileSize ) / 2.0f;
	static constexpr float radius = 0.4f;
	Collider coll;
	const TileMap& map;
	static constexpr float speed = 14.0f;
	static constexpr float jumpPower = 15.0f;
	Vec2 vel = { 0.0f,0.0f };
	static constexpr float gravAcc = 30.0f;
	static constexpr float velDecayRate = 0.97f;
	bool canJump = false;
	static constexpr float hybridJumpPower = 9.0f;
};