#include "stdafx.h"
#include "JumpState.h"
#include "AllPlayerState.h"

PlayerState * JumpState::update(Player & player)
{
	Vector3 moveDir;
	moveDir.x = 0;
	moveDir.z = 0;
	moveDir.y = 0;
	
	float lastPlayerY = player.getPosition().y;
	float lastPlayerX = player.getPosition().x;

	switch (_jumpType)
	{
		

	case JUMP_TYPE::DEFAULT_JUMP:
		moveDir.y -= player.getJumpPower();
		player.setJumpPower((player.getJumpPower() - player.getGravity()));

		if (player.getDirection() == DIRECTION::RIGHT)
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
		if (player.getDirection() == DIRECTION::LEFT)
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
	if (KEY_MANAGER->isOnceKeyDown('Z'))
	{
		AttackState* jumpAttack = new AttackState;
		jumpAttack->setSkill(ATTACK_SKILL::JUMP_QC);
		jumpAttack->setCurrJumpPower(player.getJumpPower());
		jumpAttack->setCurrMoveDirX(moveDir.x);
		return jumpAttack;
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
		moveDir.y -= player.getJumpPower();
		player.setJumpPower((player.getJumpPower() - player.getGravity()));

		if (player.getDirection() == DIRECTION::RIGHT)
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
		if (player.getDirection() == DIRECTION::LEFT)
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

	if (_jumpDirection==0)
	{
		moveDir.x += player.getSpeed()*2;
	}
	if (_jumpDirection==1)
	{
		moveDir.x -= player.getSpeed()*2;
	}
	if (KEY_MANAGER->isOnceKeyDown(VK_RIGHT))
	{
		player.setDirection(DIRECTION::RIGHT);
	}
	if (KEY_MANAGER->isOnceKeyDown(VK_LEFT))
	{
		player.setDirection(DIRECTION::LEFT);
	}

	if (KEY_MANAGER->isOnceKeyDown('Z'))
	{
		AttackState* jumpAttack = new AttackState;
		jumpAttack->setSkill(ATTACK_SKILL::JUMP_QC);
		jumpAttack->setCurrJumpPower(player.getJumpPower());
		jumpAttack->setCurrMoveDirX(moveDir.x);
		return jumpAttack;
	}

	

		break;
	case JUMP_TYPE::WALL_JUMP:

		

		if (!_ani->isPlay())
		{
			_ani->release();

			_img = IMAGE_MANAGER->findImage("Kyoko_jump");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			if (player.getDirection() == DIRECTION::LEFT)
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
			if (player.getDirection() == DIRECTION::RIGHT)
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
			if (player.getDirection() == DIRECTION::LEFT)
			{
				_jumpDirection = 0;
				player.setDirection(DIRECTION::RIGHT);
			}
			else if (player.getDirection() == DIRECTION::RIGHT)
			{
				_jumpDirection = 1;
				player.setDirection(DIRECTION::LEFT);
			}
			_ani->setFPS(15);
			_ani->start();

			player.setJumpPower(6);
			

			_jumpType = JUMP_TYPE::RUN_JUMP;
		}
		

		break;
	}

	player.move(moveDir);


	float currentPlayerY = player.getPosition().y;

	if (player.getJumpPower() < -1 && currentPlayerY == lastPlayerY&&moveDir.y!=0 &&_jumpType != JUMP_TYPE::WALL_JUMP)
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
	

	float currentPlayerX = player.getPosition().x;

	if (currentPlayerX == lastPlayerX&& moveDir.x != 0 && KEY_MANAGER->isOnceKeyDown('X'))
	{
		if (_jumpType != JUMP_TYPE::WALL_JUMP)
		{
			_jumpType = JUMP_TYPE::WALL_JUMP;
			_img = IMAGE_MANAGER->findImage("Kyoko_walljump");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			if (player.getDirection() == DIRECTION::RIGHT)
			{
				_ani->setPlayFrame(2, 4, false, false);
			}
			if (player.getDirection() == DIRECTION::LEFT)
			{
				_ani->setPlayFrame(0, 2, false, false);
			}
			_ani->setFPS(10);
			_ani->start();
		}
	}

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());

	return nullptr;
}

void JumpState::render(Player & player)
{
	_img->setScale(3);
	CAMERA_MANAGER->aniRenderZ(_img, player.getPosition(), player.getSize(), _ani, -(player.getPosition().y + (player.getSize().y / 2)));


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

	_startY = player.getPosition().y;
	
	if(_jumpType==JUMP_TYPE::RUN_JUMP)_jumpDirection = (int)player.getDirection();
	

	//_startY = player.getPosition().getIntY();
}

void JumpState::exit(Player & player)
{
	player.setJumpPower(12);
	_ani->release();
	SAFE_DELETE(_ani);
}
