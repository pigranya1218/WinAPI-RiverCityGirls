#pragma once
#include "Object.h"
class PillarObject :
	public Object
{
public:
	PillarObject(Vector3 position, DIRECTION direction);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3** pos);
};

