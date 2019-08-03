#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Collider.h"
#include "TorchHandler.h"

class Demon
{
public:
	Demon( const Vec2& pos );

	void Update( const Vec2& playerPos,float dt );
	void Draw( const TorchHandler& torchHandler,Graphics& gfx ) const;

	void Cull();

	const Collider& GetColl() const;
	bool WillCull() const;
private:
	static constexpr float radius = 0.8f;
	Collider coll;
	static constexpr float moveSpeed = 0.6f;
	bool cull = false;
};