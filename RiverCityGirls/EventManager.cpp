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
	// true반환이면 해당 이벤트는 종료해야 된다는 뜻 
	bool isEventEnd = mEventQueue[0]->EventUpdate();
	//해당 이벤트 끝났다면
	if (isEventEnd)
	{
		//삭제해주고
		SAFE_DELETE(mEventQueue[0]);
		mEventQueue.erase(mEventQueue.begin());
		//삭제해줬는데 여전히 예약되어 있는 이벤트가 있다면
		if (mEventQueue.size() != 0)
		{
			mEventQueue[0]->EventStart();
		}
	}
}

void EventManager::AddEvent(IEvent * pEvent)
{
	//만약 예약되어 있는 이벤트가 없다면
	if (mEventQueue.size() == 0)
	{
		//새로 추가하려는 이벤트의 스타트를 호출
		pEvent->EventStart();
	}
	//이벤트 추가
	mEventQueue.push_back(pEvent);
}
