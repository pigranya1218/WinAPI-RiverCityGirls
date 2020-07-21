#pragma once
#include "Enemy.h"
#include "EnemyManager.h"

class SchoolGirl : public Enemy
{
private:
	int _attackS, _attackE;


public:
	SchoolGirl() {};
	~SchoolGirl() {};

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();

	void aniPlay(ENEMY_STATE state, DIRECTION direction);
};