#include "stdafx.h"
#include "WeakAttack.h"

void WeakAttack::enter(Player & player)
{
	_img = IMAGE_MANAGER->findImage("Kyoko_attack1");
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	if (player.getDirection() == DIRECTION::RIGHT)
	{
		_ani->setPlayFrame(0, 6, false, false);
	}
	else 
	{
		_ani->setPlayFrame(6, 12, false, false);
	}

	_ani->setFPS(10);
	_ani->start();


}

PlayerState * WeakAttack::update(Player & player)
{

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());

	if (!_ani->isPlay())
	{
		return new IdleState;
	}
	else
	{
		switch (_combo)
		{
		case WeakAttack::ATTACK_COMBO::QC1:
		{
			if (2 <= _ani->getPlayIndex() && _ani->getPlayIndex() <= 3)
			{
				Vector3 position = player.getPosition();
				FloatRect attackRc = FloatRect(position.x + 50, position.y - 50,
					position.x + 150, position.y + 50);
				player.attack(attackRc, 10, ATTACK_TYPE::HIT);
			}
			if (KEY_MANAGER->isOnceKeyDown('Z'))
			{
				_img = IMAGE_MANAGER->findImage("Kyoko_attack2");

				_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
				if (player.getDirection() == DIRECTION::RIGHT)
				{
					_ani->setPlayFrame(0, 7, false, false);
				}
				else
				{
					_ani->setPlayFrame(7, 14, false, false);
				}
				_ani->setFPS(10);
				_ani->start();
				_combo = ATTACK_COMBO::QC2;
			}
		}

		break;
		case WeakAttack::ATTACK_COMBO::QC2:
			CAMERA_MANAGER->rectangle(FloatRect(300, 300, 800, 800), D2D1::ColorF::Enum::Red, 1, 20);
			if (!_ani->isPlay())
			{
				return new IdleState;
			}
			else
			{
				if (KEY_MANAGER->isOnceKeyDown('Z'))
				{
					_img = IMAGE_MANAGER->findImage("Kyoko_attack3");

					_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
					if (player.getDirection() == DIRECTION::RIGHT)
					{
						_ani->setPlayFrame(0, 7, false, false);
					}
					else
					{
						_ani->setPlayFrame(7, 14, false, false);
					}
					_ani->setFPS(10);
					_ani->start();
					_combo = ATTACK_COMBO::QC3;
				}
				
					

			}
				break;
			case WeakAttack::ATTACK_COMBO::QC3:
			    if (!_ani->isPlay())
				{
					return new IdleState;
				}
			break;
				}

			}
			return nullptr;

		
	
}
void WeakAttack::render(Player & player)
{
	_img->setScale(3);
	Vector3 position = player.getPosition();
	position.x += 35;
	CAMERA_MANAGER->rectangle(FloatRect(300, 300, 800, 800), D2D1::ColorF::Enum::Red, 1, 20);

	CAMERA_MANAGER->aniRenderZ(_img, position, player.getSize(), _ani);

}

void WeakAttack::exit(Player & paleyr)
{
	_ani->release();
	SAFE_DELETE(_ani);
}
