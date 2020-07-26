#pragma once
#include "GameObject.h"
#include "Player.h"

class EnemyManager;

enum class ENEMY_STATE
{
	IDLE,
	WALK,
	RETURN,
	RUN,	 //RUN���¿��� ATTACK -> DASH_ATTACK
	JUMP,	 //JUMP���¿��� ATTACK -> JUMP_PUNCH
	ATTACK,	 //�޺�ó�� ATTACK 1 ~ 3
	DASHATTACK,
	JUMPATTACK,
	GUARD,	 
	HIT,
	KNOCKDOWN,	 //DOWN���¿��� �ǰ� -> GROUND_HIT
	STANDUP,
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
	FloatRect _viewRc;		
	int _attackS;	// ���� ������ ������ �����

	ENEMY_STATE _state;		// ����

	Image* _enemyImg;
	Animation* _ani;		// �ִϸ��̼�
	DIRECTION _direction;	// �ִϸ��̼� �¿� ���
	DIRECTION _moveTo;		// ���� �̵� ����
	ATTACK_TYPE _hitType;	//�÷��̾�� ���� �ǰ� Ÿ��

	int _hp;				//ü��
	float _hitCount;        //�ǰ� ī��Ʈ
	int _attackCount;		//���� ī��Ʈ(ī��Ʈ ó���� �÷��̾� �˴ٿ� ��Ű��)
	float _jumpPower;       //�����Ŀ�
	float _gravity;         //�߷°�
	float _elapsedTime;		// ���� ��ȯ ��� Ÿ�̸�

	bool _isActive;			//�� ��ü ���� ����
	bool _isAttack;			//���� ó��

	float _drawYFix;		//�̹��� ���� Y�� ������

	
public:
	Enemy() {};
	~Enemy() {};

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }
	bool getHit(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type);
	bool enemyAttack(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type);
	virtual bool hitEffect(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type);
	//Vector3 playerPos = _enemyManager->getPlayerPosition(); // �÷��̾��� ��ġ
	void setDirectionToPlayer();
	
	bool isActive() { return _isActive; }


};

