#pragma once
#include "Enemy.h"
#include "EnemyManager.h"

class SchoolGirl : public Enemy
{
private:
	int _attackS, _attackE;
	bool isHit = false; //test


public:
	SchoolGirl() {};
	~SchoolGirl() {};

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();

	void aniPlay(ENEMY_STATE state, DIRECTION direction);
	virtual void hitEffect(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type);
};