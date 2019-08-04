#pragma once

#include "Sound.h"

class SoundEffect
{
public:
	SoundEffect( const std::string& fileName )
	{
		std::wstring result( fileName.length(),L' ' );

		std::copy( fileName.begin(),fileName.end(),result.begin() );

		src = Sound( result,Sound::LoopType::NotLooping );
	}

	void Play( float vol = 1.0f ) const
	{
		src.Play( 1.0f,vol );
	}
	void StopOne() const
	{
		src.StopOne();
	}
	void StopAll() const
	{
		src.StopAll();
	}
private:
	mutable Sound src;
};