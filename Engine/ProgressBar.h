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
	static constexpr int width = 34 * 3 - 6;
	static constexpr int height = 7 * 3 - 6;
	CFontPtr luckyPixel = FontCodex::Fetch( "Fonts/LuckyPixel6x9.bmp" );
	CSurfPtr lining = SurfCodex::Fetch( "Images/ProgressBar.bmp" );
};