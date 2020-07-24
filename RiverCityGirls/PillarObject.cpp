#include "stdafx.h"
#include "PillarObject.h"

PillarObject::PillarObject(Vector3 position, DIRECTION direction)
{
	_direction = direction;
	_size = Vector3(150, 100, 90);
	_position = Vector3(position.x, -(_size.y / 2), position.z);

	switch (_direction)
	{
		case DIRECTION::RIGHT:
		{_img = IMAGE_MANAGER->findImage("OBJECT_PILLAR_RIGHT"); }
		break;
		case DIRECTION::LEFT:
		{_img = IMAGE_MANAGER->findImage("OBJECT_PILLAR_LEFT"); }
		break;
	}
}

void PillarObject::update()
{
}

void PillarObject::release()
{
}

void PillarObject::render()
{
	_img->setScale(3);
	CAMERA_MANAGER->renderZ(_img, _position, _size);
}

void PillarObject::collision(Vector3 * newPoses, GameObject * gameObject)
{
}

void PillarObject::hitEffect(GameObject * hitter, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
}

