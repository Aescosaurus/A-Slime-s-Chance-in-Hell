#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "TileMap.h"
#include "Player.h"
#include "FrameTimer.h"
#include "ActionType.h"
#include "Timer.h"

class Campaign
{
public:
	Campaign( Keyboard& kbd,Mouse& mouse,Graphics& gfx );

	void Update();
	void Draw();
private:
	Keyboard& kbd;
	Mouse& mouse;
	Graphics& gfx;

	FrameTimer ft;
	TileMap map;
	Player player;
	Timer actionTimer = 1.0f;
	float chargePower = 0.0f;
};