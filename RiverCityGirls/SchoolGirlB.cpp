#include "stdafx.h"
#include "SchoolGirlB.h"

SchoolGirlB::SchoolGirlB(Vector3 position, DIRECTION direction, int imageType)
{
	_direction = direction;
	_size = Vector3(100, 330, 30);
	_position = Vector3(position.x, -(_size.y / 2), position.z);

	_idleAni = new Animation;
	if (imageType > 2) { imageType = 2; }
	if (imageType < 1) { imageType = 1; }

	switch (imageType)
	{
		case 1:
		{_img = IMAGE_MANAGER->findImage("OBJECT_schoolGirlB_idle01"); }
		break;

		case 2:
		{_img = IMAGE_MANAGER->findImage("OBJECT_schoolGirlB_idle02"); }
		break;
	}
	_idleAni->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	if (_direction == DIRECTION::LEFT)
	{
		_idleAni->setPlayFrame(0, 4, 0, 1);
	}
	if (_direction == DIRECTION::RIGHT)
	{
		_idleAni->setPlayFrame(4, 8, 0, 1);
	}
	_idleAni->setFPS(2);
	_idleAni->start();
}

void SchoolGirlB::update()
{
	_idleAni->frameUpdate(TIME_MANAGER->getElapsedTime());
}

void SchoolGirlB::release()
{
}

void SchoolGirlB::render()
{
	_img->setScale(3);
	CAMERA_MANAGER->aniRenderZ(_img, _position, _size, _idleAni);
}

void SchoolGirlB::collision(Vector3 ** pos)
{
}