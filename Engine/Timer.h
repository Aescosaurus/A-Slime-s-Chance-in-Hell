#pragma once

#include <algorithm>

class Timer
{
public:
	Timer( float time )
		:
		maxTime( time ),
		curTime( 0.0f )
	{}

	void Update( float dt )
	{
		if( curTime <= maxTime ) curTime += dt;
	}

	void Reset()
	{
		curTime = 0.0f;
	}

	bool IsDone() const
	{
		return( curTime >= maxTime );
	}
	// Returns 0-1
	float GetPercent() const
	{
		return( std::min( 1.0f,curTime / maxTime ) );
	}
private:
	float maxTime;
	float curTime;
};