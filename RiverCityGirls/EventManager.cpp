#include "stdafx.h"
#include "EventManager.h"

#include "IEvent.h"
EventManager::EventManager()
{
}


EventManager::~EventManager()
{
}

void EventManager::Update()
{
	if (mEventQueue.size() == 0)
		return;
	// true��ȯ�̸� �ش� �̺�Ʈ�� �����ؾ� �ȴٴ� �� 
	bool isEventEnd = mEventQueue[0]->EventUpdate();
	//�ش� �̺�Ʈ �����ٸ�
	if (isEventEnd)
	{
		//�������ְ�
		SAFE_DELETE(mEventQueue[0]);
		mEventQueue.erase(mEventQueue.begin());
		//��������µ� ������ ����Ǿ� �ִ� �̺�Ʈ�� �ִٸ�
		if (mEventQueue.size() != 0)
		{
			mEventQueue[0]->EventStart();
		}
	}
}

void EventManager::AddEvent(IEvent * pEvent)
{
	//���� ����Ǿ� �ִ� �̺�Ʈ�� ���ٸ�
	if (mEventQueue.size() == 0)
	{
		//���� �߰��Ϸ��� �̺�Ʈ�� ��ŸƮ�� ȣ��
		pEvent->EventStart();
	}
	//�̺�Ʈ �߰�
	mEventQueue.push_back(pEvent);
}
