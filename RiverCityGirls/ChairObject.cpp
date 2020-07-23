#include "stdafx.h"
#include "ChairObject.h"


ChairObject::ChairObject(Vector3 position, DIRECTION direction, int imageType)
{
	_direction = direction;
	_size = Vector3(150, 100, 90);
	_position = Vector3(position.x, -(_size.y / 2), position.z);

	_img = IMAGE_MANAGER->findImage("OBJECT_TABLE01");
}

void ChairObject::update()
{
}

void ChairObject::release()
{
}

void ChairObject::render()
{
	_img->setScale(2);
	CAMERA_MANAGER->renderZ(_img, _position, _size, false);
}

void ChairObject::collision(Vector3 ** pos)
{
}
