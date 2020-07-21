#include "stdafx.h"
#include "PlayerState.h"

IdleState::IdleState()
{
    _img = IMAGE_MANAGER->findImage("ÄìÄÚ´ë±â");
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(2);
	_ani->start();
}



PlayerState * IdleState::update(Player & player)
{


	if (player.getDirection() == RIGHT)
	{
		_ani->setPlayFrame(0, 12, false, true);
	}
	if (player.getDirection() == LEFT)
	{
		_ani->setPlayFrame(23, 12, false, true);
	}

	if (KEY_MANAGER->isOnceKeyDown('X'))
	{

		return new JumpState;
	}

	if (KEY_MANAGER->isOnceKeyDown(VK_RIGHT))
	{
		player.setDirection(RIGHT);
		if (_ani->getFramePos().x > 6 * _img->getMaxFrameX()) return new WalkState;
		else return new RunningState;
	}
	if (KEY_MANAGER->isOnceKeyDown(VK_LEFT))
	{
		player.setDirection(LEFT);

		if (_ani->getFramePos().x > 6 * _img->getMaxFrameX()) return new WalkState;
		else return new RunningState;
	}


	_ani->frameUpdate(TIME_MANAGER->getElapsedTime() * 10);

	return nullptr;
}

void IdleState::render(Player & player)
{
	
}

void IdleState::enter(Player & player)
{
}
