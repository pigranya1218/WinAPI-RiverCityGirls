#pragma once
#include "GameObject.h"
#include "Object.h"
#include "Player.h"

enum class OBJECT_TYPE
{
	DESK
};


class ObjectManager :  public GameObject
{
private:
	vector<Object*> _objects;

public:
	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();

	void collision(Vector3* pos);

	void spawnObject(OBJECT_TYPE type, Vector3 pos, DIRECTION direction);
};

