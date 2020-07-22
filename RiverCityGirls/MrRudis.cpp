#include "stdafx.h"
#include "MrRudis.h"

MrRudis::MrRudis(Vector3 position, DIRECTION direction)
{
	_direction = direction;
	_size = Vector3(100, 330, 30);
	_position = Vector3(position.x, -(_size.y / 2), position.z);

	_idleAni = new Animation;
	_img = IMAGE_MANAGER->findImage("OBJECT_MrRudis_idle");
	_idleAni->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	if (_direction == DIRECTION::LEFT)
	{
		_idleAni->setPlayFrame(2, 4, 0, 1);
	}
	if (_direction == DIRECTION::RIGHT)
	{
		_idleAni->setPlayFrame(0, 2, 0, 1);
	}
	_idleAni->setFPS(1);
	_idleAni->start();
}

void MrRudis::update()
{
	_idleAni->frameUpdate(TIME_MANAGER->getElapsedTime() * 10);
}

void MrRudis::release()
{
}

void MrRudis::render()
{
	_img->setScale(3);
	CAMERA_MANAGER->aniRenderZ(_img, _position, _size, _idleAni);
}

void MrRudis::collision(Vector3 ** pos)
{
}
