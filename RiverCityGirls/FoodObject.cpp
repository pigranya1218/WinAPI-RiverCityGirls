#include "stdafx.h"
#include "FoodObject.h"

FoodObject::FoodObject(Vector3 pos)
{
	_position = pos;
	_size = Vector3(10, 10, 10);
	_remainTime = 10.0f;

	_randomSpawn = RANDOM->getInt(3);

	_state = OBJECT_STATE::IDLE;
	switch (_randomSpawn)
	{
		case 0:
		{ _img = IMAGE_MANAGER->findImage("OBJECT_FOOD_APPLE"); }
		break;

		case 1:
		{ _img = IMAGE_MANAGER->findImage("OBJECT_FOOD_CHIKEN"); }
		break;

		case 2:
		{ _img = IMAGE_MANAGER->findImage("OBJECT_FOOD_CHILI"); }
		break;
	}
}

void FoodObject::update()
{
	_remainTime -= TIME_MANAGER->getElapsedTime();

	if (_remainTime <= 0)
	{
		_state = OBJECT_STATE::INACTIVE;
	}
}

void FoodObject::release()
{
}

void FoodObject::render()
{
	_img->setScale(3);
	
	if (_remainTime <= 6.0f && _remainTime >= 2.0f)
	{
		if (fmod(_remainTime, 0.2f) < 0.1f)
		{
			_img->setAlpha(1);
		}
		if (fmod(_remainTime, 0.2f) > 0.1f)
		{
			_img->setAlpha(0);
		}
	}
	else if (_remainTime < 2.0f)
	{
		if (fmod(_remainTime, 0.1f) < 0.05f)
		{
			_img->setAlpha(1);
		}
		if (fmod(_remainTime, 0.1f) > 0.05f)
		{
			_img->setAlpha(0);
		}
	}
	CAMERA_MANAGER->renderZ(_img, _position, _size);
}

void FoodObject::eatEffect(Player * gameObject)
{
	_state = OBJECT_STATE::INACTIVE;
	/*switch (_randomSpawn)
	{
		case 0:
		{ 
			if (gameObject->getHp() > 90)
			{
				gameObject->setHp(100);
			}
			gameObject->setHp(gameObject->getHp() + 10); 
		}
		break;

		case 1:
		{ gameObject->setHp(gameObject->getHp() + 30); }
		break;

		case 2:
		{ gameObject->setHp(gameObject->getHp() + 20); }
		break;
	}*/
}
