#include "stdafx.h"
#include "SchoolGirlE.h"

SchoolGirlE::SchoolGirlE(Vector3 position, DIRECTION direction, int imageType)
{
	_direction = direction;
	_size = Vector3(100, 330, 30);
	_position = Vector3(position.x, -(_size.y / 2), position.z);

	_idleAni = new Animation;
	_img = IMAGE_MANAGER->findImage("OBJECT_schoolGirlE_idle01");
	_idleAni->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	if (_direction == DIRECTION::LEFT)
	{
		_idleAni->setPlayFrame(0, 4, 0, 1);
	}
	if (_direction == DIRECTION::RIGHT)
	{
		_idleAni->setPlayFrame(4, 8, 0, 1);
	}
	_idleAni->setFPS(10);
	_idleAni->start();
}

void SchoolGirlE::update()
{
	_idleAni->frameUpdate(TIME_MANAGER->getElapsedTime());
}

void SchoolGirlE::release()
{
}

void SchoolGirlE::render()
{
	_img->setScale(3);
	CAMERA_MANAGER->aniRenderZ(_img, _position, _size, _idleAni);
}

void SchoolGirlE::collision(Vector3 ** pos)
{
}