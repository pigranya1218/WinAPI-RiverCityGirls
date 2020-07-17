#pragma once
//�������̽��� ���������Լ��� ������ �ִ� �θ� Ŭ������ ���Ѵ�
class IEvent
{
public:
	//�̺�Ʈ�� �����Ҷ� ������ �Լ�
	virtual void eventStart() = 0;
	//�̺�Ʈ ������Ʈ
	virtual bool eventUpdate() = 0;
};

class IObjectMove final : public IEvent
{
private:
	//�̵���ų ������Ʈ
	GameObject* _targetObject;
	//������
	Vector2 _targetLocation;
	//���ǵ�
	float _speed;
public:
	IObjectMove(GameObject* targetObject, Vector2 targetLocation, float speed);

	void eventStart()override;
	bool eventUpdate()override;
};

//���ʵ��� ���߰� �ϴ� �̺�Ʈ
class IWaitForSecond : IEvent
{

};