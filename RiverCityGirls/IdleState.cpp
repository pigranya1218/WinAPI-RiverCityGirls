#include "stdafx.h"
#include "AllPlayerState.h"

IdleState::IdleState()
{
    
}

PlayerState * IdleState::update(Player & player)
{
	//if (player.getDirection() == DIRECTION::RIGHT)
	//{
	//	_ani->setPlayFrame(0, 12, false, true); // 0 ~ 11
	//}
	//else if (player.getDirection() == DIRECTION::LEFT)
	//{
	//	_ani->setPlayFrame(12, 24, false, true); // 12 ~ 23
	//}

	/*if (KEY_MANAGER->isOnceKeyDown('X'))
	{
		return new JumpState;
	}*/
	if (KEY_MANAGER->isOnceKeyDown(VK_RIGHT))
	{
		player.setDirection(DIRECTION::RIGHT);
		return new WalkState;
	}
	if (KEY_MANAGER->isOnceKeyDown(VK_LEFT))
	{
		player.setDirection(DIRECTION::LEFT);
		return new WalkState;
	}
	if (KEY_MANAGER->isOnceKeyDown(VK_UP))
	{
		return new WalkState;
	}
	if (KEY_MANAGER->isOnceKeyDown(VK_DOWN))
	{
		return new WalkState;
	}

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());

	return nullptr;
}

void IdleState::render(Player & player)
{
	_img->setScale(3);
	CAMERA_MANAGER->aniRenderZ(_img, player.getPosition(), player.getSize(), _ani);
}

void IdleState::enter(Player & player)
{
	_img = IMAGE_MANAGER->findImage("ÄìÄÚ´ë±â");
	_img->setScale(3);
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(20);
	if (player.getDirection() == DIRECTION::RIGHT)
	{
		_ani->setPlayFrame(0, 12, false, true); // 0 ~ 11
	}
	else if (player.getDirection() == DIRECTION::LEFT)
	{
		_ani->setPlayFrame(12, 24, false, true); // 12 ~ 23
	}
	_ani->start();
}

void IdleState::exit(Player& player)
{
	_ani->release();
	SAFE_DELETE(_ani);
}
