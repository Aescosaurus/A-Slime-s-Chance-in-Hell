#pragma once

#include "Demon.h"
#include <vector>
#include "Timer.h"

class EnemySpawner
{
public:
	EnemySpawner( const Vei2& pos );

	void Update( const Vec2& playerPos,float dt );
	void Draw( Graphics& gfx ) const;
private:
	Vei2 pos;
	std::vector<Demon> demons;
	Timer demonSpawnTimer = 10.0f;
};