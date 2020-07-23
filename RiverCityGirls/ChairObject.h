#pragma once
#include "Object.h"
class ChairObject :
	public Object
{
public:
	ChairObject(Vector3 position, DIRECTION direction);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3** pos);
};

