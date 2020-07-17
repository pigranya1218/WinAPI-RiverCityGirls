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
	//�䷸�� �ϸ� �ܺο��� ������ ������~
	EventManager();
	~EventManager();
public:
	//�̺�Ʈ ���� ����
	//���⿡ ���� ������� �̺�Ʈ�� ó���� ����
	vector<class IEvent*> _eventQueue;

	void update();
	void addEvent(class IEvent* pEvent);
};

