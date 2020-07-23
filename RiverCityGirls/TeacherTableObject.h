#pragma once
#include "Object.h"
class TeacherTableObject :
	public Object
{
private:
public:
	TeacherTableObject(Vector3 position, DIRECTION direction);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3** pos);
};

