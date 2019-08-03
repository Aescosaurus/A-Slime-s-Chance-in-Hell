#pragma once

#include "Surface.h"
#include "Graphics.h"
#include "Timer.h"

class TorchHandler
{
public:
	class TorchItem
	{
	public:
		Vei2 pos;
		int radius = 285;
		Timer burnoutTimer = 10.0f;
	};
public:
	TorchHandler();

	void Update( float dt );
	void Draw( Graphics& gfx ) const;

	void PlaceTorch( const Vec2& pos );
	void Reset();

	const std::vector<TorchItem>& GetTorches() const;
private:
	Surface overlay;
	static constexpr float globalOpacity = 0.8f;
	static constexpr float darkenRate = 0.2f;
	std::vector<TorchItem> torches;
};