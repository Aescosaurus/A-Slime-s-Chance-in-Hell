#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "TileMap.h"
#include "Player.h"

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

	TileMap map;
	Player player;
};