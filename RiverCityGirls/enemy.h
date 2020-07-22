#pragma once
#include "GameObject.h"
#include "Player.h"

class EnemyManager;

enum class ENEMY_STATE
{
	IDLE,
	WALK,
	RUN,	 //RUN���¿��� ATTACK -> DASH_ATTACK
	JUMP,	 //JUMP���¿��� ATTACK -> JUMP_PUNCH
	ATTACK,	 //�޺�ó�� ATTACK 1 ~ 3
	DASHATTACK,
	JUMPATTACK,
	GUARD,	 
	HIT,
	DOWN,	 //DOWN���¿��� �ǰ� -> GROUND_HIT
	STUN,
	SKILL,	 //BOY(SANDTOSS), GIRL(), CHEER_GIRL()
	HELD//HELD���¿��� �ǰ� -> HELD_HIT / ���� �ð� ������ HELD_RELEASE
};

//�¿� �𷺼��� �÷��̾� ���� setFrameY�� ����

class Enemy : public GameObject
{
protected:
	EnemyManager* _enemyManager;

	FloatRect _attackRc;	// ���� ���� ��Ʈ
	ENEMY_STATE _state;		// ����

	Image* _enemyImg;
	Animation* _ani;		// �ִϸ��̼�
	DIRECTION _direction;	// �ִϸ��̼� �¿� ���
	DIRECTION _moveTo;		// ���� �̵� ����
	
	float _jumpPower;       //�����Ŀ�
	float _gravity;         //�߷°�
	float _elapsedTime;		// ���� ��ȯ ��� Ÿ�̸�

	int _attackCount;		//���� ������ ī��Ʈ
	int _dashAttackCount;	//��� ���� ������ ī��Ʈ

public:
	Enemy() {};
	~Enemy() {};

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }
	
};

