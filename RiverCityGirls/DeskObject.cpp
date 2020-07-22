#include "stdafx.h"
#include "DeskObject.h"

DeskObject::DeskObject(Vector3 position, DIRECTION direction)
{
	_direction = direction;
	_size = Vector3(300, 150, 40);
	_position = Vector3(position.x, -(_size.y / 2), position.z);

	_img = IMAGE_MANAGER->findImage("OBJECT_DESK");
}


void DeskObject::update()
{

}

void DeskObject::release()
{

}

void DeskObject::render()
{
	_img->setScale(3);
	CAMERA_MANAGER->renderZ(_img, _position, _size, false);
}

void DeskObject::collision(Vector3 ** pos)
{
}
