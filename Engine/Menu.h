#pragma once

#include "Mouse.h"
#include "Graphics.h"
#include "Button.h"
#include "Codex.h"

class Menu
{
public:
	void Update( const Mouse& mouse );
	void Draw( Graphics& gfx ) const;

	bool PressedStart() const;
private:
	Button start = Button{ Surface{ "Images/StartButton.bmp" },Vei2{ 100,300 } };
	CSurfPtr bg = SurfCodex::Fetch( "Images/MenuBackground.bmp" );
	bool pressedStart = false;
};