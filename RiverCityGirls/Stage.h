#pragma once
#include "linearFunc.h"
#include "GameObject.h"
#include "RestrictMoveLine.h"

class StageManager;
class ObjectManager;
class EnemyManager;
class Player;

struct tagDontMove // 이동 영역을 제한하기 위한 구조체
{
	LinearFunc line; // 선분
	LINEAR_VALUE_TYPE type; // 이 선분 어디를 못지나가게 할 것인가?
};

class Stage
{
protected:
	StageManager* _stageManager; 
	ObjectManager* _objectManager; 
	EnemyManager* _enemyManager;
	Player* _player;
	
	Image* _background; // 배경 이미지
	float _bgScale; // 배경이미지 배율
	vector<RestrictMoveLine*> _restrictLines; // 스테이지의 이동 영역을 제한

public:
	virtual void init(Image* background, float bgScale);
	virtual void enter();
	virtual void exit();
	virtual Stage* update();
	virtual void render();

	void setStageManager(StageManager* stageManager) { _stageManager = stageManager; }
	void setPlayer(Player* player) { _player = player; }

	// 게임 오브젝트를 가능한만큼 이동시킴
	void moveGameObject(GameObject* gameObject, Vector3 move);
	void attack(Vector3 position, FloatRect rc, float damage, ATTACK_TYPE type, vector<OBJECT_TEAM> getAttack);

	Vector3 getPlayerPosition();
};