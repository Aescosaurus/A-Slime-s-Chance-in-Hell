#pragma once

#include <string>
#include "Vec2.h"
#include "Surface.h"
#include "Mouse.h"
#include "Graphics.h"

class Button
{
public:
	Button( const Surface& image,const Vei2& pos );

	bool Update( const Mouse& mouse );
	void Draw( Graphics& gfx ) const;

	const Vei2& GetPos() const;
	bool IsHovering() const;
private:
	const Vei2 pos;
	const Surface image;
	const RectI clickArea;
	bool hovering = false;
	bool clicking = false;
	bool canClick = false;
	bool pressed = false;
};