#include "stdafx.h"
#include "IEvent.h"

#include "GameObject.h"

IObjectMove::IObjectMove(GameObject* targetObject , Vector2 targetLocation, float speed)
{
	_targetObject = targetObject;
	_targetLocation = targetLocation;
	_speed = speed;
}

void IObjectMove::eventStart()
{
}

bool IObjectMove::eventUpdate()
{
	Vector2 position = _targetObject->GetPosition();
	float angle = getAngle(position.x, position.y,
		_targetLocation.x, _targetLocation.y);

	position.x += cosf(angle) * _speed * TIMEMANAGER->getElapsedTime();
	position.y -= sinf(angle) * _speed * TIMEMANAGER->getElapsedTime();

	_targetObject->SetPosition(position);
	_targetObject->SetRect(FloatRect(position, _targetObject->GetSize(), Pivot::Center));

	//이벤트 함수에서 종료해야 될때에는 true반환
	if (getDistance(position.x, position.y, _targetLocation.x, _targetLocation.y) < 3)
	{
		_targetObject->SetPosition(_targetLocation);
		return true;
	}

	return false;
}
