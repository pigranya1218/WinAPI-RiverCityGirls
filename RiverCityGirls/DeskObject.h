#pragma once
#include "Object.h"
#include "RestrictMoveRect.h"

 class DeskObject : public Object
{
private:
	RestrictMoveRect* _restrictRect;
	

public:
	DeskObject(OBJECT_STATE state, Vector3 position, DIRECTION direction);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3* newPoses, Vector3 size);
};

