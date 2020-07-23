#include "stdafx.h"
#include "DeskChairObject.h"


DeskChairObject::DeskChairObject(OBJECT_STATE state, Vector3 position, DIRECTION direction)
{
	_state = state;
	_direction = direction;
	_size = Vector3(150, 100, 90);
	_position = Vector3(position.x, -(_size.y / 2), position.z);

	_img = IMAGE_MANAGER->findImage("OBJECT_TABLE01");
}

void DeskChairObject::update()
{
}

void DeskChairObject::release()
{
}

void DeskChairObject::render()
{
	_img->setScale(2);
	CAMERA_MANAGER->renderZ(_img, _position, _size, false);
}

void DeskChairObject::collision(Vector3 ** pos)
{
}
