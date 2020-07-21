#include "stdafx.h"
#include "AllPlayerState.h"


PlayerState * RunState::update(Player & player)
{
	Vector3 moveDir;
	moveDir.x = 0;
	moveDir.y = 0;
	moveDir.z = 0;

	if (KEY_MANAGER->isStayKeyDown(VK_RIGHT))
	{
		moveDir.x += player.getSpeed() * 2;
	}
	else if (KEY_MANAGER->isStayKeyDown(VK_LEFT))
	{
		moveDir.x -= player.getSpeed() * 2;
	}

	if (moveDir.x > 0)
	{
		player.setDirection(DIRECTION::RIGHT);
	}
	else if(moveDir.x<0)
	{
		player.setDirection(DIRECTION::LEFT);
	}
	else return new IdleState;

	player.move(moveDir);

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());

	return nullptr;
}

void RunState::render(Player & player)
{
	_img->setScale(3);
	CAMERA_MANAGER->aniRenderZ(_img, player.getPosition(), player.getSize(), _ani);
}

void RunState::enter(Player & player)
{
	_img = IMAGE_MANAGER->findImage("ÄìÄÚ´Þ¸®±â");
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(20);

	if (player.getDirection() == DIRECTION::RIGHT)
	{
		_ani->setPlayFrame(0, 16, false, true); // 0 ~ 15
	}
	else
	{
		_ani->setPlayFrame(16, 32, false, true); // 16 ~ 31
	}
	_ani->start();
}

void RunState::exit(Player & player)
{
}
