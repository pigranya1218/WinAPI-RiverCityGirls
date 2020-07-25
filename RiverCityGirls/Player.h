#pragma once
#include "GameObject.h"

class StageManager;



class PlayerState;
//class AttackState;

class Player : public GameObject
{
private:
	StageManager* _stageManager;
	//RECT _hitRc; //타격판정렉트
	

	Synthesize(float, _speed, Speed)
	Synthesize(DIRECTION, _direction, Direction)
	Synthesize(float, _jumpPower, JumpPower)
	Synthesize(float, _gravity, Gravity)
	Synthesize(int, _hp, Hp)
	Synthesize(int, _maxHp, MaxHp)
	Synthesize(bool, _onObject, OnObject)
	Synthesize(int, _exp, Exp)
	Synthesize(int, _money, Money)
	Synthesize(float, _damageTime, DamageTime)
	Synthesize(float, _damage,Damage)

	Synthesize(ATTACK_TYPE, _getHitType, GetHitType)
	 ;//적에게 맞은 공격 타입
	Synthesize(bool, _isHit, IsHit);

	float _mortalTime;
	PlayerState* _state;
	

public:
	Player();
	~Player();

	void move(Vector3 moveDir);

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();

	
	float getCenterBottom();
	void setStageManager(StageManager* stageManager) { _stageManager = stageManager; }
	void attack(FloatRect attackRc, float damage, ATTACK_TYPE type);
	void getHit(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type);
	
};

