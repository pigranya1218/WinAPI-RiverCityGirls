#pragma once
#include "GameObject.h"
#include "Player.h"

enum class OBJECT_STATE : int
{
	IDLE, // 기본 대기 상태
	REACTION, // 반응중인 상태
	BROKEN // 이미 깨져서 이제 반응 안하는 상태
};

class Object :  public GameObject
{
protected:
	OBJECT_STATE _state;					// object state
	DIRECTION _direction;

	Image* _img;								//image
	Animation* _ani;

public:
	Object() {};
	Object(Vector3 position, DIRECTION direction);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3* pos);
	virtual void reaction();
};

