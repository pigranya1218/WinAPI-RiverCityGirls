#pragma once
#include "Object.h"
class FoodObject :
	public Object
{
private:
	float _remainTime;
	int _randomSpawn;
public:
	FoodObject(Vector3 pos);
	virtual void update();
	virtual void release();
	virtual void render();

	//void isEat(Player* gameObject); // ��ġ�� ���ƴ��� üũ�ϱ� ���� �������� ���Ǵ� ��ġ üũ �Լ�
	virtual void eatEffect(Player* gameObject); // ��ġ�� ������ �� ȣ��Ǵ� �Լ�, �� ������Ʈ���� �����ϱ�
};

