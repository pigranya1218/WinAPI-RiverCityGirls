#pragma once
#include "GameObject.h"
#include "Player.h"

class EnemyManager;

enum class ENEMY_STATE
{
	DEFAULT, //�ִϸ��̼� �ѹ� ��� �Ŀ� start()�� �ݺ����� �ʰ� �ϱ� ����
	IDLE,
	WALK,
	RUN,	 //RUN���¿��� ATTACK -> DASH_ATTACK
	JUMP,	 //JUMP���¿��� ATTACK -> JUMP_PUNCH
	ATTACK,	 //�޺�ó�� ATTACK 1 ~ 3
	GUARD,	 
	HIT,
	DOWN,	 //DOWN���¿��� �ǰ� -> GROUND_HIT
	STUN,
	SKILL,	 //BOY(SANDTOSS), GIRL(), CHEER_GIRL()
	HELD	 //HELD���¿��� �ǰ� -> HELD_HIT / ���� �ð� ������ HELD_RELEASE
};

//�¿� �𷺼��� �÷��̾� ���� setFrameY�� ����

class Enemy : public GameObject
{
protected:
	EnemyManager* _enemyManager;

	FloatRect _attackRc;	// ���� ���� ��Ʈ
	ENEMY_STATE _state;	// ����

	Image* _enemyImg;
	Animation* _ani;		// �ִϸ��̼�
	DIRECTION _direction;	// �ִϸ��̼� �¿� ���
	DIRECTION _moveTo;		// ���� �̵� ����
	
	float _elapsedTime;		// ���� ��ȯ ��� Ÿ�̸�

public:
	Enemy() {};
	~Enemy() {};

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }
	
};

