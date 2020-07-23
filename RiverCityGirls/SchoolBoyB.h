#pragma once
#include "Object.h"
class SchoolBoyB :
	public Object
{
private:
	Animation* _idleAni;
	Animation* _reactionAni;
public:
	SchoolBoyB(Vector3 position, DIRECTION direction, int imageType);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3** pos);
};

