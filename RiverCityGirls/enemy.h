#pragma once
#include "gameNode.h"

enum DIRECTION
{
	IDLE,
	WALK,
	RUN,	 //RUN상태에서 ATTACK -> DASH_ATTACK
	JUMP,	 //JUMP상태에서 ATTACK -> JUMP_PUNCH
	ATTACK,	 //콤보처리 ATTACK 1 ~ 3
	GUARD,	 
	HIT,
	DOWN,	 //DOWN상태에서 피격 -> GROUND_HIT
	STUN,
	SKILL,	 //BOY(SANDTOSS), GIRL(), CHEER_GIRL()
	HELD	 //HELD상태에서 피격 -> HELD_HIT / 일정 시간 지나면 HELD_RELEASE
};
//좌우 디렉션은 플레이어 기준 setFrameY로 조정

class enemy : public gameNode
{
protected:
	Image* _enemyImg;
	FloatRect _attackRc;	//공격 렉트
	FloatRect _getHitRc;	//피격 렉트
	float  _x, _y;			//중점
	DIRECTION _direction;	//디렉션
	Animation* _ani;		//애니메이션

	int _initX, _initY;		//최초 생성 위치

public:
	enemy() {};
	~enemy() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	
};

