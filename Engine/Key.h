#pragma once

#include "Graphics.h"
#include "Collider.h"
#include "TorchHandler.h"
#include "Animation.h"
#include "Codex.h"
#include "Sound.h"

class Key
{
public:
	Key( const Vei2& pos );

	void Update( const TorchHandler& torchHandler,float dt );
	void Draw( Graphics& gfx ) const;

	void Collect();

	const Collider& GetColl() const;
	bool IsVisible() const;
	bool WillCull() const;
private:
	static constexpr float radius = 0.5f;
	Collider coll;
	bool canDraw = false;
	CSurfPtr sprSheet = SurfCodex::Fetch( "Images/Key.bmp" );
	Animation anim;
	bool collected = false;
	Vec2 vel = { 0.0f,0.0f };
	static constexpr float gravAcc = 30.0f;
	static constexpr float jumpPower = 9.5f;
	bool cull = false;
};