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
	KNOCKDOWN,	 //DOWN상태에서 피격 -> GROUND_HIT
	STANDUP,
	STUN,
	SKILL,	 //BOY(SANDTOSS), GIRL(), CHEER_GIRL()
	HELD//HELD상태에서 피격 -> HELD_HIT / 일정 시간 지나면 HELD_RELEASE
};

//좌우 디렉션은 플레이어 기준 setFrameY로 조정

class Enemy : public GameObject
{
protected:
	EnemyManager* _enemyManager;

	FloatRect _attackRc;	// 공격 판정 렉트
	FloatRect _viewRc;		
	ENEMY_STATE _state;		// 상태

	Image* _enemyImg;
	Animation* _ani;		// 애니메이션
	DIRECTION _direction;	// 애니메이션 좌우 재생
	DIRECTION _moveTo;		// 현재 이동 방향
	ATTACK_TYPE _hitType;	//플레이어에게 받은 피격 타입

	float _playerDistance;	//플레이어와의 거리
	
	int _hp;				//체력
	float _damage;			//데미지

	float _jumpPower;       //점프파워
	float _gravity;         //중력값
	float _elapsedTime;		// 상태 전환 계산 타이머

	float _lastEnemyX;		//최종 포지션x
	float _lastEnemyY;		//최종 포지션y
	float _currentEnemyX;	//현재 포지션x
	float _currentEnemyY;	//현재 포지션y

	int _attackCount;		//공격 딜레이 카운트
	int _dashAttackCount;

	bool _isGetHit;			//피격 여부

public:
	Enemy() {};
	~Enemy() {};

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }
	void getHit(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type);
	virtual void hitEffect(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type);
	void attack(FloatRect attackRc, float damage, ATTACK_TYPE type);
};

