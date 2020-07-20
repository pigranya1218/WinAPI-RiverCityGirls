#pragma once
#include "GameNode.h"
#include "SchoolBoy.h"
#include <vector>

class Enemy;

class EnemyManager : public GameNode
{
private:
	SchoolBoy* _schoolBoy;

	typedef vector<Enemy*>				vEnemy;
	typedef vector<Enemy*>::iterator	viEnemy;

	vector<POINT> _enemyRespawnPos;

protected:

public:
	EnemyManager() {};
	~EnemyManager() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void setEnemy();
	void removeEnemy(int arrNum);
};

