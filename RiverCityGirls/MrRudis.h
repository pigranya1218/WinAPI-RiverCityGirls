#pragma once
#include "Object.h"
class MrRudis :
	public Object
{
private:
	Animation* _ani;

public:
	MrRudis(OBJECT_STATE state, Vector3 position, DIRECTION direction);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3** pos);
	virtual void hitEffect(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type); // 맞았을 때 호출되는 함수, 각 오브젝트별로 구현하기
};

