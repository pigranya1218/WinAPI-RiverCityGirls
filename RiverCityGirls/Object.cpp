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
		
		CAMERA_MANAGER->drawLine(Vector2(_position.x, _position.z), Vector2(_position.x, _position.z - _size.y));
	}
}

void Object::collision(Vector3 * pos, GameObject* gameObject)
{
}

void Object::reaction()
{
}

void Object::isEat(Player * player)
{
	Vector3 playerPos = player->getPosition();
	Vector3 playerSize = player->getSize();
	float playerMinZ = playerPos.z - (playerSize.z / 2);
	float playerMaxZ = playerPos.z + (playerSize.z / 2);
	float objectMinZ = _position.z - (_size.z / 2);
	float objectMaxZ = _position.z + (_size.z / 2);
	if (objectMaxZ < playerMinZ || playerMaxZ < objectMinZ) // Z �� ��ǥ�� �������� �ʴ� ��� ����
	{
		return;
	}

	// 2. X, Y �˻� (IntersectRect)
	FloatRect playerRc = FloatRect(playerPos.x - (playerSize.x / 2), playerPos.y - (playerSize.y / 2), playerPos.x + (playerSize.x / 2), playerPos.y + (playerSize.y / 2));
	FloatRect objectRc = FloatRect(_position.x - (_size.x / 2), _position.y - (_size.y / 2), _position.x + (_size.x / 2), _position.y + (_size.y / 2));
	if (FloatRect::intersect(playerRc, objectRc))
	{
		eatEffect(player);
	}
}

void Object::eatEffect(Player * gameObject)
{
}

bool Object::getHit(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	// 1. Z�� �˻�
	Vector3 hitterPos = pos;
	Vector3 hitterSize = size;
	float hitterMinZ = hitterPos.z - (hitterSize.z / 2);
	float hitterMaxZ = hitterPos.z + (hitterSize.z / 2);
	float victimMinZ = _position.z - (_size.z / 2);
	float victimMaxZ = _position.z + (_size.z / 2);
	if (victimMaxZ < hitterMinZ || hitterMaxZ < victimMinZ) // Z �� ��ǥ�� �������� �ʴ� ��� ����
	{
		return false;
	}

	// 2. X, Y �˻� (IntersectRect)
	FloatRect victimRc = FloatRect(_position.x - (_size.x / 2), _position.y - (_size.y / 2), _position.x + (_size.x / 2), _position.y + (_size.y / 2));
	if (FloatRect::intersect(victimRc, attackRc))
	{
		return hitEffect(pos, size, team, attackRc, damage, type);
	}
	return false;
}

bool Object::hitEffect(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	return false;
}

float Object::getCenterBottom(Vector2 pos)
{
	if (!_isCollision) return 0;
	if (_position.x - (_size.x / 2) <= pos.x && pos.x <= _position.x + (_size.x / 2) &&
		_position.z - (_size.z / 2) <= pos.y && pos.y <= _position.z + (_size.z / 2))
	{
		return -_size.y;
	}
	return 0.0f;
}
