#pragma once
#include "Object.h"
class WorkingFemaleA :
	public Object
{
private:
	Animation* _idleAni;
	Animation* _reactionAni;
public:
	WorkingFemaleA(OBJECT_STATE state, Vector3 position, DIRECTION direction);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3** pos);
};
