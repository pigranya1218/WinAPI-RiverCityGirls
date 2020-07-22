#pragma once
#include "GameObject.h"
#include "Player.h"

enum class OBJECT_STATE : int
{
	IDLE, // �⺻ ��� ����
	REACTION, // �������� ����
	BROKEN // �̹� ������ ���� ���� ���ϴ� ����
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

