#pragma once
#include "GameObject.h"

enum class DIRECTION : int
{
	RIGHT,
	LEFT
};

class PlayerState;

class Player : public GameObject
{
private:
	
	RECT _rc; //피격판정렉트
	RECT _hitRc;//타격판정렉트
	float _speed;//walk 속도
	DIRECTION _direction;

	PlayerState* _state;

public:

	Player();
	~Player();

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();


	DIRECTION getDirection() { return _direction; }
	void setDirection(DIRECTION direction) { _direction = direction; }

};

