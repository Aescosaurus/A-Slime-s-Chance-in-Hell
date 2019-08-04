#pragma once

#include "Graphics.h"
#include <string>

class ProgressBar
{
public:
	void Draw( const Vei2& pos,float percent,
		Color c,const std::string& text,Graphics& gfx ) const;
private:
	static constexpr int width = 100;
	static constexpr int height = 20;
};