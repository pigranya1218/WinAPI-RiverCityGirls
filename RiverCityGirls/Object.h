#pragma once
#include "GameObject.h"
#include "Player.h"

enum class OBJECT_STATE : int
{
	IDLE01, // �⺻ ��� ����01
	IDLE02, // �⺻ ��� ����02
	IDLE03, // �⺻ ��� ����03
	IDLE04, // �⺻ ��� ����04
	REACTION, // �������� ����
	BROKEN // �̹� ������ ���� ���� ���ϴ� ����
};

class Object :  public GameObject
{
protected:
	OBJECT_STATE _state;					// object state
	DIRECTION _direction;

	Image* _img;								//image
	float _imgScale = 3;
	Animation* _ani;

public:
	Object() {};
	Object(OBJECT_STATE state, Vector3 position, DIRECTION direction);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3* newPoses, GameObject* gameObject);
	virtual void reaction();

	void getHit(Vector3 position, FloatRect attackRc, float damage, ATTACK_TYPE type); // �¾Ҵ��� üũ�ϱ� ���� �������� ���Ǵ� �浹 ó�� �Լ�
	virtual void hitEffect(Vector3 position, FloatRect attackRc, float damage, ATTACK_TYPE type); // �¾��� �� ȣ��Ǵ� �Լ�, �� ������Ʈ���� �����ϱ�
};

