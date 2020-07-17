#pragma once
//인터페이스란 순수가상함수만 가지고 있는 부모 클래스를 말한다
class IEvent
{
public:
	//이벤트가 시작할때 실행할 함수
	virtual void eventStart() = 0;
	//이벤트 업데이트
	virtual bool eventUpdate() = 0;
};

class IObjectMove final : public IEvent
{
private:
	//이동시킬 오브젝트
	GameObject* _targetObject;
	//목적지
	Vector2 _targetLocation;
	//스피드
	float _speed;
public:
	IObjectMove(GameObject* targetObject, Vector2 targetLocation, float speed);

	void eventStart()override;
	bool eventUpdate()override;
};

//몇초동안 멈추게 하는 이벤트
class IWaitForSecond : IEvent
{

};