#pragma once
#include "Object.h"
#include "RestrictMoveLine.h"

 class DeskObject : public Object
{
private:
	vector<RestrictMoveLine*> _restrictLines;
	

public:
	DeskObject(Vector3 position, DIRECTION direction);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3* pos, Vector3 size);
};

