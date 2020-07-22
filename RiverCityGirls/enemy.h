#pragma once
#include "GameObject.h"
#include "Player.h"

class EnemyManager;

enum class ENEMY_STATE
{
	IDLE,
	WALK,
	RUN,	 //RUN상태에서 ATTACK -> DASH_ATTACK
	JUMP,	 //JUMP상태에서 ATTACK -> JUMP_PUNCH
	ATTACK,	 //콤보처리 ATTACK 1 ~ 3
	DASHATTACK,
	JUMPATTACK,
	GUARD,	 
	HIT,
	DOWN,	 //DOWN상태에서 피격 -> GROUND_HIT
	STUN,
	SKILL,	 //BOY(SANDTOSS), GIRL(), CHEER_GIRL()
	HELD	 //HELD상태에서 피격 -> HELD_HIT / 일정 시간 지나면 HELD_RELEASE
};

//좌우 디렉션은 플레이어 기준 setFrameY로 조정

class Enemy : public GameObject
{
protected:
	EnemyManager* _enemyManager;

	FloatRect _attackRc;	// 공격 판정 렉트
	ENEMY_STATE _state;		// 상태

	Image* _enemyImg;
	Animation* _ani;		// 애니메이션
	DIRECTION _direction;	// 애니메이션 좌우 재생
	DIRECTION _moveTo;		// 현재 이동 방향
	
	float _jumpPower;       //점프파워
	float _gravity;         //중력값
	float _elapsedTime;		// 상태 전환 계산 타이머

	int _attackCount;		//공격 딜레이 카운트
	int _dashAttackCount;	//대시 공격 딜레이 카운트

public:
	Enemy() {};
	~Enemy() {};

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }
	
};

