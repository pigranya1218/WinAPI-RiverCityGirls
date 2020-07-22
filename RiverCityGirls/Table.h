#pragma once
#include "Object.h"
class Table :
	public Object
{
private:
public:
	Table(Vector3 position, DIRECTION direction);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3** pos);
};

