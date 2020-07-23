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
	DeskObject(OBJECT_STATE state, Vector3 position, DIRECTION direction);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3* newPoses, GameObject* gameObject);
	virtual void hitEffect(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type); // �¾��� �� ȣ��Ǵ� �Լ�, �� ������Ʈ���� �����ϱ�
};

