/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteEffect.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	cam( wnd.kbd,wnd.mouse,gfx )
{
	wnd.Maximize();
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

Game::~Game()
{
	SoundCodex::Purge(); // Errors happen without this.. :(
}

void Game::UpdateModel()
{
	if( wnd.kbd.KeyIsPressed( VK_CONTROL ) &&
		wnd.kbd.KeyIsPressed( 'W' ) )
	{
		wnd.Kill();
	}

	switch( gameState )
	{
	case State::Menu:
		menu.Update( wnd.mouse );
		if( menu.PressedStart() ) gameState = State::Game;
		break;
	case State::Game:
		cam.Update2();
		break;
	}
}

void Game::ComposeFrame()
{
	switch( gameState )
	{
	case State::Menu:
		menu.Draw( gfx );
		break;
	case State::Game:
		cam.Draw();
		break;
	}
	gfx.DrawSprite( wnd.mouse.GetPosX(),
		wnd.mouse.GetPosY(),cursorSpr,false,
		SpriteEffect::Chroma{} );
}
