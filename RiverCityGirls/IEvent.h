#pragma once
//인터페이스란 순수가상함수만 가지고 있는 부모 클래스를 말한다
class IEvent
{
public:
	//이벤트가 시작할때 실행할 함수
	virtual void EventStart() = 0;
	//이벤트 업데이트
	virtual bool EventUpdate() = 0;
};

class IObjectMove final : public IEvent
{
	//이동시킬 오브젝트
	class GameObject* mTargetObject;
	//목적지
	Vector2 mTargetLocation;
	//스피드
	float mSpeed;
public:
	IObjectMove(GameObject* targetObject, Vector2 targetLocation, float speed);

	void EventStart()override;
	bool EventUpdate()override;
};

//몇초동안 멈추게 하는 이벤트
class IWaitForSecond : IEvent
{

};