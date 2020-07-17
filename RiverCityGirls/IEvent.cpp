#include "stdafx.h"
#include "IEvent.h"

#include "GameObject.h"

IObjectMove::IObjectMove(GameObject* targetObject , Vector2 targetLocation, float speed)
{
	mTargetObject = targetObject;
	mTargetLocation = targetLocation;
	mSpeed = speed;
}

void IObjectMove::EventStart()
{
}

bool IObjectMove::EventUpdate()
{
	Vector2 position = mTargetObject->GetPosition();
	float angle = getAngle(position.x, position.y,
		mTargetLocation.x, mTargetLocation.y);

	position.x += cosf(angle) * mSpeed * TIMEMANAGER->getElapsedTime();
	position.y -= sinf(angle) * mSpeed * TIMEMANAGER->getElapsedTime();

	mTargetObject->SetPosition(position);
	mTargetObject->SetRect(FloatRect(position, mTargetObject->GetSize(), Pivot::Center));

	//�̺�Ʈ �Լ����� �����ؾ� �ɶ����� true��ȯ
	if (getDistance(position.x, position.y, mTargetLocation.x, mTargetLocation.y) < 3)
	{
		mTargetObject->SetPosition(mTargetLocation);
		return true;
	}

	return false;
}
