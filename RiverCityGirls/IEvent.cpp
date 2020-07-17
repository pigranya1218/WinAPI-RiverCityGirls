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

	//�̺�Ʈ �Լ����� �����ؾ� �ɶ����� true��ȯ
	if (getDistance(position.x, position.y, _targetLocation.x, _targetLocation.y) < 3)
	{
		_targetObject->SetPosition(_targetLocation);
		return true;
	}

	return false;
}
