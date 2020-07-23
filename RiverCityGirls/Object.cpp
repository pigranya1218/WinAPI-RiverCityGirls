#include "stdafx.h"
#include "Object.h"

Object::Object(OBJECT_STATE state, Vector3 position, DIRECTION direction)
{
	_state = state;
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

void Object::getHit(Vector3 position, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
}

void Object::hitEffect(Vector3 position, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
}
