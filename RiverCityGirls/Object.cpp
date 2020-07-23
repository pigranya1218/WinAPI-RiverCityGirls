#include "stdafx.h"
#include "Object.h"

Object::Object(Vector3 position, DIRECTION direction, int imageType)
{
	_position = position;
	_direction = direction;
}

void Object::update()
{
}

void Object::release()
{
}

void Object::render()
{
	_img->setScale(3);

	if (DEBUG_MANAGER->isDebugMode(DEBUG_TYPE::OBJECT))
	{
		_img->setAlpha(0.5);
	}
}

void Object::collision(Vector3 * pos, GameObject* gameObject)
{
}

void Object::reaction()
{
}

void Object::getHit(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	// 1. Z축 검사
	Vector3 hitterPos = hitter->getPosition();
	Vector3 hitterSize = hitter->getSize();
	float hitterMinZ = hitterPos.z - (hitterSize.z / 2);
	float hitterMaxZ = hitterPos.z + (hitterSize.z / 2);
	float victimMinZ = _position.z - (_size.z / 2);
	float victimMaxZ = _position.z + (_size.z / 2);
	if (victimMaxZ < hitterMinZ || hitterMaxZ < victimMinZ) // Z 축 좌표가 공유되지 않는 경우 종료
	{
		return;
	}

	// 2. X, Y 검사 (IntersectRect)
	FloatRect victimRc = FloatRect(_position.x - (_size.x / 2), _position.y - (_size.y / 2), _position.x + (_size.x / 2), _position.y + (_size.y / 2));
	if (FloatRect::intersect(victimRc, attackRc))
	{
		hitEffect(hitter, attackRc, damage, type);
	}
}

void Object::hitEffect(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
}
