#include "stdafx.h"
#include "SchoolBoyA.h"

SchoolBoyA::SchoolBoyA(Vector3 position, DIRECTION direction, int imageType)
{
	_imageType = imageType;
	_direction = direction;
	_size = Vector3(100, 330, 30);
	_position = Vector3(position.x, -(_size.y / 2), position.z);

	_ani = new Animation;
	if (imageType > 2) { imageType = 2; }
	if (imageType < 1) { imageType = 1; }

	switch (imageType)
	{
		case 1:
		{_img = IMAGE_MANAGER->findImage("OBJECT_schoolBoyA_idle01"); }
		break;

		case 2:
		{_img = IMAGE_MANAGER->findImage("OBJECT_schoolBoyA_idle02"); }
		break;
	}
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	if (_direction == DIRECTION::LEFT)
	{
		_ani->setPlayFrame(0, 4, 0, 1);
	}
	if (_direction == DIRECTION::RIGHT)
	{
		_ani->setPlayFrame(4, 8, 0, 1);
	}
	_ani->setFPS(2);
	_ani->start();
}

void SchoolBoyA::update()
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
				switch (_imageType)
				{
					case 1:
					{_img = IMAGE_MANAGER->findImage("OBJECT_schoolBoyA_idle01");}
					break;

					case 2:
					{_img = IMAGE_MANAGER->findImage("OBJECT_schoolBoyA_idle02"); }
					break;
				}

				_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
				if (_direction == DIRECTION::LEFT)
				{
					_ani->setPlayFrame(0, 4, false, true);
				}
				if (_direction == DIRECTION::RIGHT)
				{
					_ani->setPlayFrame(4, 8, false, true);
				}
				_ani->setFPS(3);
				_ani->start();
				_state = OBJECT_STATE::IDLE;
			}
		}
		break;
	}
	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());
}

void SchoolBoyA::release()
{
	_ani->release();
	delete _ani;
}

void SchoolBoyA::render()
{
	_img->setScale(3);
	CAMERA_MANAGER->aniRenderZ(_img, _position, _size, _ani);
}

void SchoolBoyA::collision(Vector3 ** pos)
{
}

void SchoolBoyA::hitEffect(GameObject * hitter, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	if (_state != OBJECT_STATE::REACTION)
	{
		_state = OBJECT_STATE::REACTION;
		_img = IMAGE_MANAGER->findImage("OBJECT_schoolBoyA_reaction");
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		if (_direction == DIRECTION::LEFT)
		{
			_ani->setPlayFrame(0, 3, false, false);
		}
		if (_direction == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(3, 6, false, false);
		}
		_ani->setFPS(6);
		_ani->start();
	}
}