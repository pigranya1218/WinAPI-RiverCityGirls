#pragma once
#include "Object.h"
class SchoolBoyA :
	public Object
{
private:
	Animation* _ani;
	Animation* _reactionAni;
	int _imageType;
public:
	SchoolBoyA(Vector3 position, DIRECTION direction, int imageType);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3** pos);
	void hitEffect(GameObject * hitter, FloatRect attackRc, float damage, ATTACK_TYPE type);
};

