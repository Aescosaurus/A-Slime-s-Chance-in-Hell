#pragma once

#include "Graphics.h"
#include "Collider.h"
#include "TorchHandler.h"

class Key
{
public:
	Key( const Vei2& pos );

	void Update( const TorchHandler& torchHandler,float dt );
	void Draw( Graphics& gfx ) const;

	const Collider& GetColl() const;
	bool IsVisible() const;
private:
	static constexpr float radius = 0.4f;
	Collider coll;
	bool canDraw = false;
};