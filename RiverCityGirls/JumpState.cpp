#include "stdafx.h"
#include "JumpState.h"
#include "AllPlayerState.h"

PlayerState * JumpState::update(Player & player)
{
	Vector3 moveDir;
	moveDir.x = 0;
	moveDir.z = 0;
	moveDir.y = 0;

	moveDir.y -= player.getJumpPower();
	player.setJumpPower((player.getJumpPower() - _gravity));
	float lastPlayerY = player.getPosition().y;

	if (player.getDirection() == DIRECTION:: RIGHT)
	{
		if (player.getJumpPower() > 2)
		{
			_ani->setPlayFrame(0, 1, false, false);
		}
		if (player.getJumpPower() < -1)
		{
			_ani->setPlayFrame(2, 1, false, false);
		}
		if (player.getJumpPower() >= -1 && player.getJumpPower() <= 2)
		{
			_ani->setPlayFrame(1, 2, false, false);
		}
	}
	if (player.getDirection() == DIRECTION:: LEFT)
	{
		if (player.getJumpPower() > 2)
		{
			_ani->setPlayFrame(3, 4, false, false);
		}
		if (player.getJumpPower() < -1)
		{
			_ani->setPlayFrame(5, 4, false, false);
		}
		if (player.getJumpPower() >= -1 && player.getJumpPower() <= 2)
		{
			_ani->setPlayFrame(4, 5, false, false);
		}
	}

	switch (_jumpType)
	{
	case JUMP_TYPE::DEFAULT_JUMP:

	if (KEY_MANAGER->isStayKeyDown(VK_RIGHT))
	{
		moveDir.x += player.getSpeed();
	}
	if (KEY_MANAGER->isStayKeyDown(VK_LEFT))
	{
		moveDir.x -= player.getSpeed();
	}

	if (KEY_MANAGER->isStayKeyDown(VK_UP))
	{
		moveDir.z -= player.getSpeed()/2;
	}
	else if (KEY_MANAGER->isStayKeyDown(VK_DOWN))
	{
		moveDir.z += player.getSpeed()/2;
	}

	if (moveDir.x > 0)
	{
		player.setDirection(DIRECTION::RIGHT);
	}
	if (moveDir.x < 0)
	{
		player.setDirection(DIRECTION::LEFT);
	}
	break;
	case JUMP_TYPE::RUN_JUMP:


		break;
	}

	player.move(moveDir);

	float currentPlayerY = player.getPosition().y;

	if (player.getJumpPower() < -0.4 && currentPlayerY == lastPlayerY)
	{
		if (KEY_MANAGER->isStayKeyDown(VK_RIGHT) || KEY_MANAGER->isStayKeyDown(VK_LEFT))
		{
			return new WalkState;
		}
		else
		{
			return new IdleState;
		}
	}


	_ani->frameUpdate(TIME_MANAGER->getElapsedTime() * 10);

	return nullptr;
}

void JumpState::render(Player & player)
{
	_img->setScale(3);
	CAMERA_MANAGER->aniRenderZ(_img, player.getPosition(), player.getSize(), _ani, true);

	/*char str[254];
	sprintf_s(str, "moveDir.x:%d,moveDir.y:%u,moveDir.z:%d ,direction:%d ", moveDir.x, moveDir.y, moveDir.z, player.getDirection());
	TextOut(_hdc,0,100 ,str, strlen(str));*/
}

void JumpState::enter(Player & player)
{
	
	_img = IMAGE_MANAGER->findImage("Kyoko_jump");
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, false);
	_ani->setFPS(15);
	_ani->start();

	_gravity = 0.3f;
	//_startY = player.getPosition().getIntY();
}

void JumpState::exit(Player & player)
{
	player.setJumpPower(12);
	_ani->release();
	SAFE_DELETE(_ani);
}
