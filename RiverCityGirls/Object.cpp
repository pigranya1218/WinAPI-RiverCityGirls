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
}

void Object::collision(Vector3 * pos, const Vector3 size)
{

}

void Object::reaction()
{
}