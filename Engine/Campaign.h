#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "TileMap.h"
#include "Player.h"
#include "FrameTimer.h"
#include "ActionType.h"
#include "Timer.h"
#include "TorchHandler.h"
#include "EnemySpawner.h"

class Campaign
{
public:
	Campaign( Keyboard& kbd,Mouse& mouse,Graphics& gfx );

	void Update();
	void Draw();
private:
	void PlayerJump();
private:
	Keyboard& kbd;
	Mouse& mouse;
	Graphics& gfx;

	FrameTimer ft;
	TileMap map;
	Player player;
	Timer actionTimer = 1.0f;
	float chargePower = 0.0f;
	bool jumping = false;
	bool placingTorch = false;
	static constexpr float chargeRate = 1.0f;
	Vec2 diff;
	TorchHandler torchHandler;
	EnemySpawner enemySpawner;
};