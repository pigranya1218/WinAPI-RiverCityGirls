#include "stdafx.h"
#include "AllPlayerState.h"

PlayerState * WalkState::update(Player& player)
{

	Vector3 moveDir;
	moveDir.x = 0;
	moveDir.y = 0;
	moveDir.z = 0;

	if (KEY_MANAGER->isStayKeyDown(VK_RIGHT))
	{
		moveDir.x += player.getSpeed();
	}
	else if (KEY_MANAGER->isStayKeyDown(VK_LEFT))
	{
		moveDir.x -= player.getSpeed();
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
		player.setDirection(DIRECTION::RIGHT);
	}
	else if (moveDir.x < 0)
	{
		player.setDirection(DIRECTION::LEFT);
	}

	// TODO :: 움직임 대각석으로 움직일 때 보정하기

	
	if (moveDir.x == 0 && moveDir.z == 0)
	{

		_state = WALK_STATE::IDLE;
		// 후처리 이미지으로 바꾸기
		// 후처리 애니메이션 설정하고 스타트
	}
	else
	{
		_state = WALK_STATE::MOVE;
	}

	switch (_state)
	{
	case WALK_STATE::MOVE:
	{
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(0, 12, false, true); // 0 ~ 11
		}
		else
		{
			_ani->setPlayFrame(12, 24, false, true); // 12 ~ 23
		}

		if (_initTime <= 0.5)
		{
			_initTime += TIME_MANAGER->getElapsedTime();
			if ((player.getDirection() == DIRECTION::RIGHT && KEY_MANAGER->isOnceKeyDown(VK_RIGHT))
				&& (player.getDirection() == DIRECTION::LEFT && KEY_MANAGER->isOnceKeyDown(VK_LEFT)))
			{
				return new RunState;
			}
		}

		player.move(moveDir);
		
	}
	break;
	case WALK_STATE::IDLE:
	{
		//if (player.getDirection() == DIRECTION::RIGHT)
		//{
		//	// TODO
		//}
		//else
		//{
		//	// TODO
		//}
		//if (!_ani->isPlay())
		//{
		//	return new IdleState;
		//}
		return new IdleState;
	}
	break;
	}

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());

	return nullptr;
}

void WalkState::render(Player& player)
{
	_img->setScale(3);
	CAMERA_MANAGER->aniRenderZ(_img, player.getPosition(), player.getSize(), _ani);
}


void WalkState::enter(Player& player)
{
	_img = IMAGE_MANAGER->findImage("쿄코걷기");
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(20);

	if (player.getDirection() == DIRECTION::RIGHT)
	{
		_ani->setPlayFrame(0, 12, false, true); // 0 ~ 11
	}
	else
	{
		_ani->setPlayFrame(12, 24, false, true); // 12 ~ 23
	}
	_ani->start();

	_initTime = 0;
	_state = WALK_STATE::MOVE;
}

void WalkState::exit(Player& player)
{
	_ani->release();
	SAFE_DELETE(_ani);
}