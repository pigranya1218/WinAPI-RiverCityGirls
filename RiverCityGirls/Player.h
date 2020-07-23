#pragma once
#include "GameObject.h"

class StageManager;

enum class DIRECTION : int
{
	RIGHT,
	LEFT
};

enum class ATTACK_TYPE : int
{
	HIT,
	KNOCKDOWN
};

class PlayerState;
//class AttackState;

class Player : public GameObject
{
private:
	StageManager* _stageManager;
	//RECT _hitRc; //Ÿ��������Ʈ
	
	Synthesize(float, _speed, Speed)
	Synthesize(DIRECTION, _direction, Direction)
	Synthesize(float, _jumpPower, JumpPower)

	PlayerState* _state;

	//AttackState* _attackState;

public:
	Player();
	~Player();

	void move(Vector3 moveDir);

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setStageManager(StageManager* stageManager) { _stageManager = stageManager; }
	void attack(FloatRect attackRc, float damage, ATTACK_TYPE type);
	void getHit(Vector3 position, FloatRect attackRc, float damage, ATTACK_TYPE type);
	
};

