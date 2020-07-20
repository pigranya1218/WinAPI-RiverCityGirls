#pragma once
#include "gameNode.h"
#include "schoolBoy.h"
#include <vector>

class enemy;

class enemyManager : public gameNode
{
private:
	schoolBoy* _schoolBoy;

	typedef vector<enemy*>				vEnemy;
	typedef vector<enemy*>::iterator	viEnemy;

	vector<POINT> _enemyRespawnPos;

protected:

public:
	enemyManager() {};
	~enemyManager() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void setEnemy();
	void removeEnemy(int arrNum);
};

