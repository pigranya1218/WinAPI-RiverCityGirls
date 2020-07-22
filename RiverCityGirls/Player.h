#pragma once
#include "GameObject.h"

class StageManager;

enum class DIRECTION : int
{
	RIGHT,
	LEFT
};

class PlayerState;

class Player : public GameObject
{
private:
	StageManager* _stageManager;
	RECT _hitRc; //타격판정렉트
	
	Synthesize(float, _speed, Speed)
	Synthesize(DIRECTION, _direction, Direction)
	Synthesize(float, _jumpPower, JumpPower)

	PlayerState* _state;

public:
	Player();
	~Player();

	void move(Vector3 moveDir);

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setStageManager(StageManager* stageManager) { _stageManager = stageManager; }
	
};

