#pragma once
#include "Object.h"
class SchoolGirlB :
	public Object
{
private:
	Animation* _idleAni;
	Animation* _reactionAni;
public:
	SchoolGirlB(Vector3 position, DIRECTION direction);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3** pos);
};