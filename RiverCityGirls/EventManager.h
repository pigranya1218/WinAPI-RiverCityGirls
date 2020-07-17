#pragma once
class EventManager
{
public:
	static EventManager* getInstance()
	{
		static EventManager* instance = new EventManager;
		return instance;
	}
private:
	//요렇게 하면 외부에서 생성을 못하지~
	EventManager();
	~EventManager();
public:
	//이벤트 담을 변수
	//여기에 들어온 순서대로 이벤트를 처리할 예정
	vector<class IEvent*> _eventQueue;

	void update();
	void addEvent(class IEvent* pEvent);
};

