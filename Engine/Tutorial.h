#pragma once

#include "Codex.h"
#include <string>
#include "ActionType.h"
#include "Timer.h"

class Tutorial
{
public:
	void Update( const Vei2& drawPos,float dt );
	void Draw( Graphics& gfx ) const;

	void CompleteAction( ActionType act );

	bool LightPlayer() const;
private:
	CFontPtr luckyPixel = FontCodex::Fetch( "Fonts/LuckyPixel6x9.bmp" );

	int curHint = 0;
	Timer nextHintTimer = 3.5f;
	Vei2 drawPos = { 0,0 };

	std::vector<std::string> hints =
	{
		"Welcome!  This tutorial will teach you the basics.",
		"Click and hold on the player to place a torch.",
		"Good!  Place torches to see keys and enemies.",
		"Click on an empty area of the screen to jump.",
		"Good job!  Now look and see if you can find a key.",
		"You must be near a key to collect it.",
		"There it is!",
		"Find an enemy.  Click and hold to shoot it!",
		"Good!  Looks like you're ready for the real thing.",
		"Collect the final key to start the game.",
		""
	};
	std::vector<ActionType> requiredActions =
	{
		ActionType::PlaceTorch,
		ActionType::Jump,
		ActionType::CollectKey,
		ActionType::Attack,
		ActionType::CollectKey
	};
};