#pragma once
#include "Object.h"
#include "RestrictMoveRect.h"

 class DeskObject : public Object
{
private:
	RestrictMoveRect* _restrictRect;
	int _collisionOffsetX = 15;
	int _collisionOffsetZ = 10;

public:
	DeskObject(Vector3 position, DIRECTION direction, int imageType);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3* newPoses, GameObject* gameObject);
};

