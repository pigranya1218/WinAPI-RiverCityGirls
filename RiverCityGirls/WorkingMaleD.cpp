#include "stdafx.h"
#include "WorkingMaleD.h"

WorkingMaleD::WorkingMaleD(OBJECT_STATE state, Vector3 position, DIRECTION direction)
{
	_state = state;
	_direction = direction;
	_size = Vector3(100, 330, 30);
	_position = Vector3(position.x, -(_size.y / 2), position.z);

	_idleAni = new Animation;
	_img = IMAGE_MANAGER->findImage("OBJECT_workingMaleD_idle01");
	_idleAni->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	if (_direction == DIRECTION::LEFT)
	{
		_idleAni->setPlayFrame(0, 12, 0, 1);
	}
	if (_direction == DIRECTION::RIGHT)
	{
		_idleAni->setPlayFrame(12, 24, 0, 1);
	}
	_idleAni->setFPS(1);
	_idleAni->start();
}

void WorkingMaleD::update()
{
	_idleAni->frameUpdate(TIME_MANAGER->getElapsedTime() * 2);
}

void WorkingMaleD::release()
{
}

void WorkingMaleD::render()
{
	_img->setScale(3);
	CAMERA_MANAGER->aniRenderZ(_img, _position, _size, _idleAni, true);
}

void WorkingMaleD::collision(Vector3 ** pos)
{
}