#pragma once

#include "Surface.h"
#include "Graphics.h"

class Animation
{
public:
	Animation( int x,int y,int width,int height,int count,
		const Surface& sheet,float holdTime,
		Color chroma = Colors::Magenta );

	void Update( float dt );
	template<typename Effect>
	void Draw( const Vei2& pos,Graphics& gfx,
		bool centered,Effect eff ) const
	{
		gfx.DrawSprite( pos.x,pos.y,frames[curFrame],
			*sheet,centered,eff );
	}

	void Reset();
	void RandomizeCurFrame();

	bool IsDone() const;
private:
	const Surface* sheet;
	float holdTime;
	Color chroma;
	std::vector<RectI> frames;
	float curFrameTime = 0.0f;
	int curFrame = 0;
	bool finished = false;
};