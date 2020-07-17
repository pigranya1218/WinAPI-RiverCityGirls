#pragma once
class EventManager
{
public:
	//싱글턴 만드는 방법중에 하나
	//양쌤이 만들어준 싱글톤과의 차이점은
	//1) 상속을 쓰느냐 안쓰느냐
	//2) 데이터영역(실질적으로는 BSS)
	//3) 마찬가지로 처음 호출하면 instance 메모리를 잡는다
	static EventManager* GetInstance()
	{
		static EventManager instance;
		return &instance;
	}
private:
	//요렇게 하면 외부에서 생성을 못하지~
	EventManager();
	~EventManager();
public:
	//이벤트 담을 변수
	//여기에 들어온 순서대로 이벤트를 처리할 예정
	vector<class IEvent*> mEventQueue;

	void Update();
	void AddEvent(class IEvent* pEvent);
};

