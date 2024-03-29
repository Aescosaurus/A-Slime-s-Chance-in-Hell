#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Collider.h"
#include "TorchHandler.h"
#include "Timer.h"
#include "Codex.h"
#include "Animation.h"

class Demon
{
public:
	Demon( const Vec2& pos );

	void Update( const Vec2& playerPos,const TorchHandler& torchHandler,float dt );
	void UpdateNoMove( const TorchHandler& torchHandler,float dt );
	void Draw( Graphics& gfx ) const;

	void Cull();
	void SetPos( const Vec2& pos );

	const Collider& GetColl() const;
	bool WillCull() const;
	bool IsVisible() const;
private:
	static constexpr float radius = 0.6f;
	Collider coll;
	static constexpr float moveSpeed = 0.6f;
	bool cull = false;
	bool canDraw = false;
	Vec2 vel = { 0.0f,0.0f };
	Timer retargetTimer = 1.0f;
	CSurfPtr sprSheet = SurfCodex::Fetch( "Images/Demon.bmp" );
	Animation anim;
	CSoundPtr ouchSound = SoundCodex::Fetch( "Sounds/EnemyOuch.wav" );
};