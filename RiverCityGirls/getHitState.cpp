#include "stdafx.h"
#include "AllPlayerState.h"

void getHitState::enter(Player & player)
{
	_img = IMAGE_MANAGER->findImage("Kyoko_gethit");
	_img->setScale(3);
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(15);
	if (player.getDirection() == DIRECTION::RIGHT)
	{
		_ani->setPlayFrame(0, 4, false, false); // 0 ~ 3
	}
	else if (player.getDirection() == DIRECTION::LEFT)
	{
		_ani->setPlayFrame(12, 16, false, false); // 12 ~ 15
	}
	_ani->start();
}

void getHitState::exit(Player & player)
{
	_ani->release();
	SAFE_DELETE(_ani)
}

PlayerState * getHitState::update(Player & player)
{
	switch (_getHitState)
	{
	case GET_HIT_STATE::GET_HIT:
		//player.setHp(player.getHp()-damage)

		if (!_ani->isPlay())
		{
			return new IdleState;
		}
		else
		{

		}

		break;
	case GET_HIT_STATE::KNOCK_OUT:
		break;
	case GET_HIT_STATE::KNOCK_DOWN:
		break;
	case GET_HIT_STATE::STAND_UP:
		break;
	}

	return nullptr;
}

void getHitState::render(Player & player)
{
	_img->setScale(3);
	CAMERA_MANAGER->aniRenderZ(_img, player.getPosition(), player.getSize(), _ani);
}
