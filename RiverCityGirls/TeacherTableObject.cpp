#include "stdafx.h"
#include "TeacherTableObject.h"


TeacherTableObject::TeacherTableObject(Vector3 position, DIRECTION direction)
{
	_direction = direction;
	_size = Vector3(150, 100, 90);
	_position = Vector3(position.x, -(_size.y / 2), position.z);

	_img = IMAGE_MANAGER->findImage("OBJECT_TEACHER_TABLE");
}

void TeacherTableObject::update()
{
}

void TeacherTableObject::release()
{
}

void TeacherTableObject::render()
{
	_img->setScale(2);
	CAMERA_MANAGER->renderZ(_img, _position, _size, false);
}

void TeacherTableObject::collision(Vector3 ** pos)
{
}
