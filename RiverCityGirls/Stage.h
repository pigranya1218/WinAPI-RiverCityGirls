#pragma once
#include "linearFunc.h"
#include "GameObject.h"

class StageManager;
class ObjectManager;
class EnemyManager;
class Player;

class Stage
{
protected:
	struct tagDontMove // �������� �̵� ������ �����ϱ� ���� ����ü
	{
		LinearFunc line; // ����
		LINEAR_VALUE_TYPE type; // �� ���� ��� ���������� �� ���ΰ�?
	};
protected:
	StageManager* _stageManager; 
	ObjectManager* _objectManager; 
	EnemyManager* _enemyManager;
	Player* _player;
	
	Image* _background; // ��� �̹���
	float _bgScale; // ����̹��� ����
	vector<tagDontMove> _linearFuncs; // ���������� �̵� ������ ����

public:
	virtual void init(Image* background, float bgScale);
	virtual void enter() {};
	virtual void exit() {};
	virtual Stage* update();
	virtual void render();

	void setStageManager(StageManager* stageManager) { _stageManager = stageManager; }
	void setPlayer(Player* player) { _player = player; }

	void pushLine(LinearFunc line, LINEAR_VALUE_TYPE type) { _linearFuncs.push_back({ line, type }); }

	// ���� ������Ʈ�� �����Ѹ�ŭ �̵���Ŵ
	void moveGameObject(GameObject& gameObject, Vector3 move);
	
};