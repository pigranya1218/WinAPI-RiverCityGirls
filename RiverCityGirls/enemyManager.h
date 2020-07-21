#pragma once
#include "GameObject.h"
#include <vector>

class SchoolBoy;
class Enemy;
class Stage;

class EnemyManager
{
private:
	using vEnemy = vector<Enemy*>;
	using viEnemy = vector<Enemy*>::iterator;

private:
	Stage* _stage;
	
	SchoolBoy* _schoolBoy;
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
	void moveEnemy(GameObject* enemy, Vector3 dir);

	void setStage(Stage* stage) { _stage = stage; }
	Vector3 getPlayerPosition();
};

