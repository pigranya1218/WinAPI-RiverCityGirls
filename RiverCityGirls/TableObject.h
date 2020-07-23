#pragma once
#include "Object.h"

class TableObject :
	public Object
{
private:
public:
	TableObject(Vector3 position, DIRECTION direction);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3** pos);
};

