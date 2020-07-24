#pragma once
#include "Object.h"
class SchoolStudent :
	public Object
{
private:
	Animation* _ani;
	Animation* _reactionAni;
	int _imageType;
public:
	SchoolStudent(Vector3 position, DIRECTION direction, int imageType);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3** pos);
	void hitEffect(GameObject * hitter, FloatRect attackRc, float damage, ATTACK_TYPE type);
};

