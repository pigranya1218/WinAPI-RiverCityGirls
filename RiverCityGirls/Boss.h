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
	GROUND_ATTACK, // �ɾ��ִ� ������� ����
	STAND_UP, // �ɾ��ִ� �Ͼ�� ����
	METEOR_ATTACK, // ���� �� ������� ����
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

	float _down; // ��ġ�� ���� �̻� �Ѿ�� �˴ٿ� ��
	int _count; // ���� ��鿡�� ���� ���¿��� ���Ǵ� ī��Ʈ

public:
	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setState(BOSS_STATE state, DIRECTION direction);
	virtual void hitEffect(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type);
	void setAttackState(BOSS_PHASE phase);
};

