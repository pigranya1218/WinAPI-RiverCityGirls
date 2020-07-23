#pragma once
#include "Object.h"
#include "RestrictMoveRect.h"

class SnackMachineObject :
	public Object
{
private:
	RestrictMoveRect* _restrictRect;
	int _collisionOffsetX = 5;
	int _collisionOffsetZ = 0;
public:
	SnackMachineObject(Vector3 position, DIRECTION direction);

	virtual void update();
	virtual void release();
	virtual void render();
	void collision(Vector3 * newPoses, GameObject * gameObject);
	void hitEffect(GameObject * hitter, FloatRect attackRc, float damage, ATTACK_TYPE type);
	//virtual void collision(Vector3** pos);
};

