#pragma once

#include "Demon.h"
#include <vector>
#include "Timer.h"
#include "TorchHandler.h"

class EnemySpawner
{
public:
	void Update( const Vec2& playerPos,float dt );
	void Draw( const TorchHandler& torchHandler,Graphics& gfx ) const;

	void AddPos( const Vei2& pos );
private:
	std::vector<Vei2> spawnPosList;
	std::vector<Demon> demons;
	Timer demonSpawnTimer = 1.0f; // from 7
};