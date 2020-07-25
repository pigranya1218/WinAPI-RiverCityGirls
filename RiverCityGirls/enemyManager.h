#pragma once
#include "GameObject.h"
#include <vector>

class SchoolBoy;
class SchoolGirl;
class CheerGirl;
class Boss;
class Enemy;
class Stage;

enum class ENEMY_TYPE : int
{
	SCHOOL_BOY,
	SCHOOL_GIRL,
	CHEER_GIRL,
	BOSS
};


class EnemyManager
{
private:
	Stage* _stage;

	vector<Enemy*> _enemies;
	vector<POINT> _enemyRespawnPos;

protected:

public:
	EnemyManager() {};
	~EnemyManager() {};

	void init();
	void release();
	void update();
	void render();

	void moveEnemy(GameObject* enemy, Vector3 dir);
	void spawnEnemy(ENEMY_TYPE type, Vector2 pos);
	void clearEnemy();

	void setStage(Stage* stage) { _stage = stage; }
	int getEnemyCount() { return _enemies.size(); }
	Vector3 getPlayerPosition();
	float getCenterBottom(Vector3 pos);
	
	void setBossUiVisible(bool isVisible);
	void setBossUi(float currHp, float maxHp);

	void getHit(GameObject* gameObject, FloatRect attackRc, float damage, ATTACK_TYPE type);
	void enemyAttack(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type);
	void enemyAttackObject(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type);
};

