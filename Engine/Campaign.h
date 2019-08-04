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
#include "Bullet.h"
#include "Key.h"
#include "ProgressBar.h"
#include "Tutorial.h"
#include "Button.h"

class Campaign
{
public:
	Campaign( Keyboard& kbd,Mouse& mouse,Graphics& gfx );

	// void Update();
	bool Update2();
	void Draw();
private:
	// void PlayerJump();
	void LoadNextLevel();
private:
	Keyboard& kbd;
	Mouse& mouse;
	Graphics& gfx;

	FrameTimer ft;
	TileMap map;
	Player player;
	int curLevel = -1;
	static constexpr int nLevels = 1;
	CFontPtr luckyPixel = FontCodex::Fetch( "Fonts/LuckyPixel6x9.bmp" );
	const std::vector<std::string> winText =
	{
		"You have defeated the demons and escaped hell!",
		"Thank you for taking the time to play this game.",
		"I hope you had as much fun playing as I did dev'ing.",
		"It would be awesome if you shared with your friends,",
		"Or left an honest comment or rating.",
		"But please don't feel obligated to do so.",
		"Thanks again for playing, I'll see you next time!",
		"-Aesc"
	};
	Vec2 textPos = Vec2( Vei2{ Graphics::GetScreenRect().GetCenter().x,
		Graphics::ScreenHeight } );
	static constexpr float textMoveSpeed = 15.0f;
	Button quitButton = Button{ Surface{ "Images/QuitButton1.bmp" },Graphics::GetScreenRect().GetCenter() + Vei2::Down() * 200 - Vei2{ 43,20 } * 3 / 2 };
	bool showQuitButton = false;

	// Timer actionTimer = 1.0f;
	// float chargePower = 0.0f;
	// bool jumping = false;
	// bool placingTorch = false;
	// bool hoveringEnemy = false;
	// static constexpr float chargeRate = 1.0f;
	// Vec2 diff;

	ActionType curAction = ActionType::None;
	ActionType testAction = ActionType::None;
	Timer startAction = 0.2f;
	Timer chargeTimer = 1.0f;

	TorchHandler torchHandler;
	EnemySpawner enemySpawner;
	std::vector<Bullet> bullets;
	std::vector<Key> keys;
	int selectedKey = -1;
	static constexpr float keyCollectDist = 2.5f;
	Timer hurtTimer = 1.0f;

	const Surface background = "Images/Background.bmp";
	ProgressBar pb;
	std::string actionName = "";
	Demon tutorialDemon;
	Tutorial tut;
};