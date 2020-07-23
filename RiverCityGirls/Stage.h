#pragma once
#include "linearFunc.h"
#include "GameObject.h"
#include "RestrictMoveLine.h"

class StageManager;
class ObjectManager;
class EnemyManager;
class Player;

struct tagDontMove // �̵� ������ �����ϱ� ���� ����ü
{
	LinearFunc line; // ����
	LINEAR_VALUE_TYPE type; // �� ���� ��� ���������� �� ���ΰ�?
};

class Stage
{
protected:
	StageManager* _stageManager; 
	ObjectManager* _objectManager; 
	EnemyManager* _enemyManager;
	Player* _player;
	
	Image* _background; // ��� �̹���
	float _bgScale; // ����̹��� ����
	vector<RestrictMoveLine*> _restrictLines; // ���������� �̵� ������ ����

public:
	virtual void init(Image* background, float bgScale);
	virtual void enter();
	virtual void exit();
	virtual Stage* update();
	virtual void render();

	void setStageManager(StageManager* stageManager) { _stageManager = stageManager; }
	void setPlayer(Player* player) { _player = player; }

	// ���� ������Ʈ�� �����Ѹ�ŭ �̵���Ŵ
	void moveGameObject(GameObject* gameObject, Vector3 move);
	void attack(Vector3 position, FloatRect rc, float damage, ATTACK_TYPE type, vector<OBJECT_TEAM> getAttack);

	Vector3 getPlayerPosition();
};