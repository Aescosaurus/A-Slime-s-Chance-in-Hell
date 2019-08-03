#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Collider.h"
#include "TorchHandler.h"

class Demon
{
public:
	Demon( const Vec2& pos );

	void Update( const Vec2& playerPos,const TorchHandler& torchHandler,float dt );
	void Draw( Graphics& gfx ) const;

	void Cull();

	const Collider& GetColl() const;
	bool WillCull() const;
	bool IsVisible() const;
private:
	static constexpr float radius = 0.8f;
	Collider coll;
	static constexpr float moveSpeed = 0.6f;
	bool cull = false;
	bool canDraw = false;
};