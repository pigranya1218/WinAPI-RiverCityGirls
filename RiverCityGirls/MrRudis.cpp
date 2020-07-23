#include "stdafx.h"
#include "MrRudis.h"

MrRudis::MrRudis(Vector3 position, DIRECTION direction)
{
	_direction = direction;
	_size = Vector3(100, 330, 30);
	_position = Vector3(position.x, -(_size.y / 2), position.z);

	_ani = new Animation;
	_img = IMAGE_MANAGER->findImage("OBJECT_MrRudis_idle");
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	if (_direction == DIRECTION::LEFT)
	{
		_ani->setPlayFrame(2, 4, 0, 1);
	}
	if (_direction == DIRECTION::RIGHT)
	{
		_ani->setPlayFrame(0, 2, 0, 1);
	}
	_ani->setFPS(10);
	_ani->start();
}

void MrRudis::update()
{
	switch (_state)
	{
	case OBJECT_STATE::IDLE:
	{
	}
	break;
	case OBJECT_STATE::REACTION:
	{

		if (!_ani->isPlay())
		{
			_img = IMAGE_MANAGER->findImage("OBJECT_MrRudis_idle");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			if (_direction == DIRECTION::LEFT)
			{
				_ani->setPlayFrame(2, 4, false, true);
			}
			if (_direction == DIRECTION::RIGHT)
			{
				_ani->setPlayFrame(0, 2, false, true);
			}
			_ani->setFPS(10);
			_ani->start();
			_state = OBJECT_STATE::IDLE;
		}
	}
	break;
	}

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());
}

void MrRudis::release()
{
	_ani->release();
	delete _ani;
}

void MrRudis::render()
{
	_img->setScale(3);
	CAMERA_MANAGER->aniRenderZ(_img, _position, _size, _ani);
}

void MrRudis::collision(Vector3 ** pos)
{
}

void MrRudis::hitEffect(GameObject * hitter, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	if (_state != OBJECT_STATE::REACTION)
	{
		_state = OBJECT_STATE::REACTION;
		_img = IMAGE_MANAGER->findImage("OBJECT_MrRudis_reaction");
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		if (_direction == DIRECTION::LEFT)
		{
			_ani->setPlayFrame(5, 10, false, false);
		}
		if (_direction == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(0, 5, false, false);
		}
		_ani->setFPS(15);
		_ani->start();
	}
}