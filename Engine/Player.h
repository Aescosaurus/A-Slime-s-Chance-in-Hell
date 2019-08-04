#pragma once

#include "Vec2.h"
#include "TileMap.h"
#include "Graphics.h"
#include "Collider.h"
#include "ActionType.h"
#include "Codex.h"
#include "Animation.h"
#include "Timer.h"

class Player
{
public:
	enum class State
	{
		Idle,
		Charge,
		Jump
	};
public:
	Player( const TileMap& map );

	void Update( float dt );
	void Draw( Graphics& gfx ) const;

	void Move( const Vec2& diff );
	// void Jump( const Vec2& diff );
	void HybridJump( const Vec2& diff );
	// void Shoot( const Vec2& diff );
	void Reset();
	void ChargeJump();
	void Idlize();
	void Cull();

	const Collider& GetColl() const;
	bool WillCull() const;
private:
	void SwitchAction( State state );
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
	static constexpr float hybridJumpPower = 29.0f;
	CSurfPtr sprSheet = SurfCodex::Fetch( "Images/Player.bmp" );
	Animation idle;
	Animation charge;
	Animation jump;
	State action = State::Idle;
	Timer goIdleTimer = 0.1f;
	bool cull = false;
	bool startedCull = false;
	static constexpr float cullJumpPower = 9.5f;
};