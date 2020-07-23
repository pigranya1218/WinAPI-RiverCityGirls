#pragma once
#include "GameObject.h"
#include "Player.h"

enum class OBJECT_STATE : int
{
	IDLE01, // 기본 대기 상태01
	IDLE02, // 기본 대기 상태02
	IDLE03, // 기본 대기 상태03
	IDLE04, // 기본 대기 상태04
	REACTION, // 반응중인 상태
	BROKEN // 이미 깨져서 이제 반응 안하는 상태
};

class Object :  public GameObject
{
protected:
	OBJECT_STATE _state;					// object state
	DIRECTION _direction;

	Image* _img;								//image
	float _imgScale = 3;
	Animation* _ani;

public:
	Object() {};
	Object(OBJECT_STATE state, Vector3 position, DIRECTION direction);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3* newPoses, const Vector3 size);
	virtual void reaction();
};

