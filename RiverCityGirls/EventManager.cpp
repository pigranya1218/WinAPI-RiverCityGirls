#include "stdafx.h"
#include "EventManager.h"

#include "IEvent.h"
EventManager::EventManager()
{
}


EventManager::~EventManager()
{
}

void EventManager::update()
{
	if (_eventQueue.size() == 0)
		return;
	// true��ȯ�̸� �ش� �̺�Ʈ�� �����ؾ� �ȴٴ� �� 
	bool isEventEnd = _eventQueue[0]->eventUpdate();
	//�ش� �̺�Ʈ �����ٸ�
	if (isEventEnd)
	{
		//�������ְ�
		SAFE_DELETE(_eventQueue[0]);
		_eventQueue.erase(_eventQueue.begin());
		//��������µ� ������ ����Ǿ� �ִ� �̺�Ʈ�� �ִٸ�
		if (_eventQueue.size() != 0)
		{
			_eventQueue[0]->eventStart();
		}
	}
}

void EventManager::addEvent(IEvent * pEvent)
{
	//���� ����Ǿ� �ִ� �̺�Ʈ�� ���ٸ�
	if (_eventQueue.size() == 0)
	{
		//���� �߰��Ϸ��� �̺�Ʈ�� ��ŸƮ�� ȣ��
		pEvent->eventStart();
	}
	//�̺�Ʈ �߰�
	_eventQueue.push_back(pEvent);
}
