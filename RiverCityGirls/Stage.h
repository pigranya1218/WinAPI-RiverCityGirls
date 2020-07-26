#pragma once
#include "linearFunc.h"
#include "GameObject.h"
#include "RestrictMoveLine.h"
#include "UIManager.h"
#include "DialogueManager.h"

class StageManager;
class ObjectManager;
class EnemyManager;
class Player;

struct tagDontMove // �̵� ������ �����ϱ� ���� ����ü
{
	LinearFunc line; // ����
	LINEAR_VALUE_TYPE type; // �� ���� ��� ���������� �� ���ΰ�?
};

struct tagDoorDestination
{
	string destName;
	Vector3 destPos;
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
	vector<tagDoorInfo> _doorInfos; // ���������� ��
	vector<tagDoorDestination> _doorDestination; // ���������� �� ������

public:
	virtual void init(Image* background, float bgScale);
	virtual void release();
	virtual void enter();
	virtual void exit();
	virtual Stage* update();
	virtual void render();

	void setStageManager(StageManager* stageManager) { _stageManager = stageManager; }
	void setPlayer(Player* player) { _player = player; }

	// ���� ������Ʈ�� �����Ѹ�ŭ �̵���Ŵ
	void moveGameObject(GameObject* gameObject, Vector3 move);
	bool attack(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect rc, float damage, ATTACK_TYPE type, vector<OBJECT_TEAM> getAttack);

	void setBossUiVisible(bool isVisible);
	void setBossUi(float currHp, float maxHp);
	void startDialogue(BossChapter chapter);
	bool isDialoging();
	void setHeart(bool isVisible);
	void spawnMoney(Vector3 pos);

	virtual void gameOver();

	float getCenterBottom(Vector3 pos);
	Vector3 getPlayerPosition();
	float getPlayerHp();
};