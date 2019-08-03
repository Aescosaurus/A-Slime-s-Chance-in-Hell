#pragma once

#include "Demon.h"
#include <vector>
#include "Timer.h"
#include "TorchHandler.h"

class EnemySpawner
{
public:
	void Update( const Vec2& playerPos,const TorchHandler& torchHandler,float dt );
	void Draw( Graphics& gfx ) const;

	void AddPos( const Vei2& pos );
	void Reset();

	std::vector<Demon>& GetEnemies();
private:
	std::vector<Vei2> spawnPosList;
	std::vector<Demon> demons;
	Timer demonSpawnTimer = 7.0f;
};