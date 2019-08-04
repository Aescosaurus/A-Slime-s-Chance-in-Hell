#pragma once

#include "Graphics.h"
#include <string>
#include "Codex.h"

class ProgressBar
{
public:
	void Draw( const Vei2& pos,float percent,
		Color c,const std::string& text,Graphics& gfx ) const;
private:
	static constexpr int width = 100;
	static constexpr int height = 20;
	CFontPtr luckyPixel = FontCodex::Fetch( "Fonts/LuckyPixel6x9.bmp" );
};