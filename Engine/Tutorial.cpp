#include "Tutorial.h"

void Tutorial::Update( const Vei2& drawPos,float dt )
{
	this->drawPos = drawPos;

	if( curHint % 2 == 0 )
	{
		nextHintTimer.Update( dt );
		if( nextHintTimer.IsDone() )
		{
			nextHintTimer.Reset();
			++curHint;
		}
	}
}

void Tutorial::Draw( Graphics& gfx ) const
{
	luckyPixel->DrawTextCentered( hints[curHint],
		Graphics::GetScreenRect().GetCenter(),
		Colors::White,gfx );
}

void Tutorial::CompleteAction( ActionType act )
{
	if( act == requiredActions[curHint / 2] )
	{
		++curHint;
	}
}

bool Tutorial::LightPlayer() const
{
	return( curHint == 1 );
}
