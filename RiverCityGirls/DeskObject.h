#pragma once
#include "Object.h"
#include "RestrictMoveRect.h"

 class DeskObject : public Object
{
private:
	Animation* _frameAni;
	RestrictMoveRect* _restrictRect;
	int _collisionOffsetX = 15;
	int _collisionOffsetZ = 10;
	int _imageType;
	int _frameX;
	int _frameTime;
public:
	DeskObject(Vector3 position, DIRECTION direction, int imageType);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3* newPoses, GameObject* gameObject);
	virtual void hitEffect(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type); // 맞았을 때 호출되는 함수, 각 오브젝트별로 구현하기
};

