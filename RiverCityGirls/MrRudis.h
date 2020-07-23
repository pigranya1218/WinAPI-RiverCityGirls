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
	virtual void hitEffect(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type); // �¾��� �� ȣ��Ǵ� �Լ�, �� ������Ʈ���� �����ϱ�
};

