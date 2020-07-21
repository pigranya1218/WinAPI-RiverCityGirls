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

	// TODO :: ������ �밢������ ������ �� �����ϱ�

	
	if (moveDir.x == 0 && moveDir.z == 0)
	{
		if (_state != WALK_STATE::IDLE)
		{
			_state = WALK_STATE::IDLE;
			_img = IMAGE_MANAGER->findImage("���ڴ��");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			if (player.getDirection() == DIRECTION::RIGHT)
			{
				_ani->setPlayFrame(0, 12, false, false); // 0 ~ 11

			}
			else
			{
				_ani->setPlayFrame(12, 24, false, false); // 12 ~ 23

			}

			_ani->setFPS(20);
			_ani->start();
		}

		// ��ó�� �̹������� �ٲٱ�
		// ��ó�� �ִϸ��̼� �����ϰ� ��ŸƮ
	}
	else
	{
		if (_state != WALK_STATE::MOVE)
		{
			_state = WALK_STATE::MOVE;
			_img = IMAGE_MANAGER->findImage("���ڰȱ�");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setFPS(20);
			_ani->start();
			_initTime = 0;
		}
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

		
		moveDir = Vector3::normalize(&moveDir);
		moveDir = moveDir * player.getSpeed();
		player.move(moveDir);
		
	}
	break;
	case WALK_STATE::IDLE:
	{
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(0, 12, false, false); // 0 ~ 11
			
		}
		else
		{
			_ani->setPlayFrame(12, 24, false, false); // 12 ~ 23
			
		}

		if (!_ani->isPlay())
		{
			
			return new IdleState;
		}
		

		//return new IdleState;
	}
	break;
	}
	if (_initTime <= 0.5)
	{
		_initTime += TIME_MANAGER->getElapsedTime();
		if ((player.getDirection() == DIRECTION::RIGHT && KEY_MANAGER->isOnceKeyDown(VK_RIGHT))
			|| (player.getDirection() == DIRECTION::LEFT && KEY_MANAGER->isOnceKeyDown(VK_LEFT)))
		{
			return new RunState;
		}
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
	_img = IMAGE_MANAGER->findImage("���ڰȱ�");
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