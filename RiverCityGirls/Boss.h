#pragma once
#include "enemyManager.h"
#include "enemy.h"

enum class BOSS_PHASE
{
	PHASE_1,
	PHASE_2,
	PHASE_3,
	DEFEAT
};

enum class BOSS_STATE
{
	IDLE, // ��� ����
	WALK, // �÷��̾�� �ɾ���� ����, ���� ���� ��� ����
	LAUGH, // ���� ����, �� Ÿ�̹�
	GROUND, // �ɾ��ִ� ����
	STAND_UP, // �ɾ��ִ� �Ͼ�� ����
	METEOR_ATTACK, // ���� �� ������� ����
	METEOR_ATTACK_DELAY, // ������� �� �����ϱ�
	ROAR, // ������ ��ȯ�Ҷ� ���¢��
	STRONG_PUNCH, // ���Ƽ� ��ġ ������
	WEAK_PUNCH_COMBO, // 3�� ������
	DASH_ATTACK, // �÷��̾� ȣ���ϸ鼭 �޷���
	GET_HIT, // �´� ����
	GROUND_HIT, // �ɾ��ִٰ� �´� ����
	KNOCKDOWN, // �¾� ���󰡴� ����
};

class Boss : public Enemy
{
private:
	BOSS_PHASE _phase;
	BOSS_STATE _bossState;

	float _combo; // 3�� �޺������� �¾���
	float _electricTime;
	int _count; // ���� ��鿡�� ���� ���¿��� ���Ǵ� ī��Ʈ

	bool _checkDialog;
	int _maxHp;

public:
	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setState(BOSS_STATE state, DIRECTION direction, bool initTime);
	virtual bool hitEffect(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type);
	void setAttackState(BOSS_PHASE phase, float playerDistance);
};

