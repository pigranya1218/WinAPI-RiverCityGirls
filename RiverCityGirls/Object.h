#pragma once
#include "GameObject.h"
#include "Player.h"

enum class OBJECT_STATE : int
{
	IDLE, // �⺻ ��� ����
	REACTION, // �������� ����
	BROKEN, // �̹� ������ ���� ���� ���ϴ� ����
	INACTIVE // �������� �԰ų� �ð��� �ٵǾ ������� ����
};

class ObjectManager;

class Object :  public GameObject
{
protected:
	ObjectManager* _objectManager;
	OBJECT_STATE _state;					// object state
	DIRECTION _direction;

	Image* _img;								//image
	float _imgScale = 3;
	Animation* _ani;

	bool _isCollision = false;

public:
	Object() {};
			//
	Object(Vector3 position, DIRECTION direction, int imageType);

	inline OBJECT_STATE getState() { return _state; }

	void setObjectManager(ObjectManager* objectManager) { _objectManager = objectManager; }

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3* newPoses, GameObject* gameObject);
	virtual void reaction();

	void isEat(Player* gameObject); // ��ġ�� ���ƴ��� üũ�ϱ� ���� �������� ���Ǵ� ��ġ üũ �Լ�
	virtual void eatEffect(Player* gameObject); // ��ġ�� ������ �� ȣ��Ǵ� �Լ�, �� ������Ʈ���� �����ϱ�
	bool getHit(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type); // �¾Ҵ��� üũ�ϱ� ���� �������� ���Ǵ� �浹 ó�� �Լ�
	virtual bool hitEffect(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type); // �¾��� �� ȣ��Ǵ� �Լ�, �� ������Ʈ���� �����ϱ�
	float getCenterBottom(Vector2 pos);
};

