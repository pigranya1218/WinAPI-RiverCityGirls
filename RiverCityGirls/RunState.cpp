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

	if (KEY_MANAGER->isStayKeyDown(VK_UP))
	{
		moveDir.z -= player.getSpeed();
	}
	else if (KEY_MANAGER->isStayKeyDown(VK_DOWN))
	{
		moveDir.z += player.getSpeed();
	}

	if (moveDir.x > 0)
	{
		_ani->setPlayFrame(0, 16, false, true);
		player.setDirection(DIRECTION::RIGHT);
	}
	else if(moveDir.x<0)
	{
		_ani->setPlayFrame(16, 32, false, true);
		player.setDirection(DIRECTION::LEFT);
	}
	else return new IdleState;

	moveDir = Vector3::normalize(&moveDir);
	moveDir = moveDir * player.getSpeed()*2;
	player.move(moveDir);

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());

	return nullptr;
}

void RunState::render(Player & player)
{
	_img->setScale(3);
	CAMERA_MANAGER->aniRenderZ(_img, player.getPosition(), player.getSize(), _ani, true);
}

void RunState::enter(Player & player)
{
	_img = IMAGE_MANAGER->findImage("Kyoko_run");
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
	_ani->release();
	SAFE_DELETE(_ani);
}
