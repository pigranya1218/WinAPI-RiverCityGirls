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
	
	RECT _rc; //�ǰ�������Ʈ
	RECT _hitRc;//Ÿ��������Ʈ
	float _speed;//walk �ӵ�
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

