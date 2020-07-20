#pragma once
#include "GameNode.h"

enum DIRECTION
{
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

class Enemy : public GameNode
{
protected:
	Image* _enemyImg;
	FloatRect _attackRc;	//���� ��Ʈ
	FloatRect _getHitRc;	//�ǰ� ��Ʈ
	float  _x, _y;			//����
	DIRECTION _direction;	//�𷺼�
	Animation* _ani;		//�ִϸ��̼�

	int _initX, _initY;		//���� ���� ��ġ

public:
	Enemy() {};
	~Enemy() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	
};

