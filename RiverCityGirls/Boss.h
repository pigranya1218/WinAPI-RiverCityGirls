#pragma once
#include "enemyManager.h"
#include "enemy.h"
class Boss : public Enemy
{
private:



public:
	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();

	void aniPlay(ENEMY_STATE state, DIRECTION direction);
};

