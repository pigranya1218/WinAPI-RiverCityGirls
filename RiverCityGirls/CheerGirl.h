#pragma once
#include "Enemy.h"
#include "EnemyManager.h"


class CheerGirl :public Enemy
{

private:
	int _attackS, _attackE;


public:
	CheerGirl() {};
	~CheerGirl() {};

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();

	void aniPlay(ENEMY_STATE state, DIRECTION direction);
};
