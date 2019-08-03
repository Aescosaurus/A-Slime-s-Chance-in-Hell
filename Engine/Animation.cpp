#include "Animation.h"
#include "Random.h"

Animation::Animation( int x,int y,int width,int height,int count,
	const Surface& sheet,float holdTime,Color chroma )
	:
	sheet( &sheet ),
	holdTime( holdTime ),
	chroma( chroma )
{
	for( int i = 0; i < count; ++i )
	{
		frames.emplace_back( x + i * width,
			x + ( i + 1 ) * width,y,y + height );
	}
}

void Animation::Update( float dt )
{
	curFrameTime += dt;
	while( curFrameTime >= holdTime )
	{
		++curFrame;
		if( curFrame >= int( frames.size() ) )
		{
			curFrame = 0;
			finished = true;
		}

		curFrameTime -= holdTime;
	}
}

void Animation::Reset()
{
	curFrameTime = 0.0f;
	curFrame = 0;
	finished = false;
}

void Animation::RandomizeCurFrame()
{
	curFrameTime = float( Random{ 0.0f,holdTime *
		int( frames.size() ) } );
}

bool Animation::IsDone() const
{
	return( finished );
}
