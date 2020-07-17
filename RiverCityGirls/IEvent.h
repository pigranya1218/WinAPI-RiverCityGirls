#pragma once
//�������̽��� ���������Լ��� ������ �ִ� �θ� Ŭ������ ���Ѵ�
class IEvent
{
public:
	//�̺�Ʈ�� �����Ҷ� ������ �Լ�
	virtual void EventStart() = 0;
	//�̺�Ʈ ������Ʈ
	virtual bool EventUpdate() = 0;
};

class IObjectMove final : public IEvent
{
	//�̵���ų ������Ʈ
	class GameObject* mTargetObject;
	//������
	Vector2 mTargetLocation;
	//���ǵ�
	float mSpeed;
public:
	IObjectMove(GameObject* targetObject, Vector2 targetLocation, float speed);

	void EventStart()override;
	bool EventUpdate()override;
};

//���ʵ��� ���߰� �ϴ� �̺�Ʈ
class IWaitForSecond : IEvent
{

};