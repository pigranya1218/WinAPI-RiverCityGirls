#include "stdafx.h"
#include "Object.h"

Object::Object(Vector3 position, DIRECTION direction)
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
}

void Object::collision(Vector3 * pos, GameObject* gameObject)
{
}

void Object::reaction()
{
}