#pragma once
#include "Object.h"
class MrRudis :
	public Object
{
private:
	Animation* _idleAni;
	Animation* _reactionAni;
public:
	MrRudis(OBJECT_STATE state, Vector3 position, DIRECTION direction);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3** pos);
};

