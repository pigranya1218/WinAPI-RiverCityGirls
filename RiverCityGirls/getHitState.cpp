#include "stdafx.h"
#include "AllPlayerState.h"

void getHitState::enter(Player & player)
{
	

	_getHitType = player.getGetHitType();
	
	switch (_getHitType)
	{
	case ATTACK_TYPE::HIT1:
		_getHitState = GET_HIT_STATE::HIT;
		break;
	case ATTACK_TYPE::HIT2:
		_getHitState = GET_HIT_STATE::HIT2;
		break;
	case ATTACK_TYPE::KNOCKDOWN:
		_getHitState = GET_HIT_STATE::KNOCK_DOWN;
		break;
	}
	setGetHitAni(player);
	
	_downTime = 0;
	_airBorne = 1;
	_hitDelay = 0;
	_stunTime = 0;
	player.setHp(player.getHp() - player.getDamage());//플레이어 체력 깍는 것
	player.setIsHit(true);
}

void getHitState::exit(Player & player)
{
	player.setIsHit(false);
	_ani->release();
	SAFE_DELETE(_ani)
}

PlayerState * getHitState::update(Player & player)
{
	

	moveDir.x = 0;
	moveDir.y += player.getGravity();
	moveDir.z = 0;

	

	switch (_getHitState)
	{
	case GET_HIT_STATE::HIT:

		
			lastPlayerY = player.getPosition().y;
			moveDir.x += (player.getDirection() == DIRECTION::RIGHT) ? -0.3 : 0.3;
			
			player.move(moveDir);
			currentPlayerY = player.getPosition().y;
		
			if (!_ani->isPlay())
			{

				return new IdleState;
			}
		

		break;




	case GET_HIT_STATE::HIT2:
		

		
			lastPlayerY = player.getPosition().y;
			moveDir.x += (player.getDirection() == DIRECTION::RIGHT) ? -0.3 : 0.3;
			//moveDir.y += player.getGravity();
			player.move(moveDir);
			currentPlayerY = player.getPosition().y;

			

		
		
			if (!_ani->isPlay())
			{
				return new IdleState;
			}
		
		

		break;
	case GET_HIT_STATE::KNOCK_DOWN:
		

		
		if (!_ani->isPlay())
		{
			
			if (_downTime <= 1)
			{
				_downTime += TIME_MANAGER->getElapsedTime();
			}
			
			else
			{
				if (player.getHp() <= 0)
				{
					_getHitState = GET_HIT_STATE::GAME_OVER;
					setGetHitAni(player);
				}
				else
				{
					_getHitState = GET_HIT_STATE::STAND_UP;
					setGetHitAni(player);
				}
			}
		}
		else
		{
			lastPlayerY = player.getPosition().y;
			moveDir.x += (player.getDirection() == DIRECTION::RIGHT) ? -1 : 1;
			moveDir.y -= _airBorne;
			_airBorne -= player.getGravity();
			player.move(moveDir);
			currentPlayerY = player.getPosition().y;
		}

		break;
	case GET_HIT_STATE::STAND_UP:
		
		if (!_ani->isPlay())
		{
			int stunPer = RANDOM->getInt(100);

			if (stunPer < 10)
			{
				_getHitState = GET_HIT_STATE::STUN;
				setGetHitAni(player);
			}
			else return new IdleState;
		}

		break;
	case GET_HIT_STATE::STUN:
		
		_stunTime += TIME_MANAGER->getElapsedTime();
		if (_stunTime>3)
		{
			return new IdleState;
			
		}
		break;
	case GET_HIT_STATE::GAME_OVER:

		break;

	}

	

	
	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());

	return nullptr;
}

void getHitState::render(Player & player)
{
	Vector3 position;
	position = player.getPosition();
	if (_getHitState == GET_HIT_STATE::STAND_UP)
	{
		position.y += 25;
	}
	if (_getHitState == GET_HIT_STATE::KNOCK_DOWN)
	{
		position.y -= 10;
	}
	if (_getHitState == GET_HIT_STATE::GAME_OVER)
	{
		position.y += 25;
	}
	_img->setScale(3);
	CAMERA_MANAGER->aniRenderZ(_img, position, player.getSize(), _ani);
}

void getHitState::setGetHitAni(Player& player)
{
	switch (_getHitState)
	{
	case GET_HIT_STATE::HIT:
		_img = IMAGE_MANAGER->findImage("Kyoko_gethit");
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setFPS(10);
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(0, 4, false, false); // 0 ~ 3
		}
		else if (player.getDirection() == DIRECTION::LEFT)
		{
			_ani->setPlayFrame(12, 16, false, false); // 12 ~ 15
		}
		_ani->start();
		break;
	case GET_HIT_STATE::HIT2:
		_img = IMAGE_MANAGER->findImage("Kyoko_gethit");
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setFPS(20);
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(4, 8, false, false); // 0 ~ 3
		}
		else if (player.getDirection() == DIRECTION::LEFT)
		{
			_ani->setPlayFrame(16, 20, false, false); // 12 ~ 15
		}
		_ani->start();
		break;
	case GET_HIT_STATE::KNOCK_DOWN:
		_img = IMAGE_MANAGER->findImage("Kyoko_knockout");
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setFPS(20);
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(4, 24, false, false); //
		}
		else if (player.getDirection() == DIRECTION::LEFT)
		{
			_ani->setPlayFrame(28, 48, false, false); // 
		}
		_ani->start();
		break;
	case GET_HIT_STATE::STAND_UP:
		_img = IMAGE_MANAGER->findImage("Kyoko_standup");
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setFPS(20);
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(0, 9, false, false); //
		}
		else if (player.getDirection() == DIRECTION::LEFT)
		{
			_ani->setPlayFrame(9, 18, false, false); // 
		}
		_ani->start();
		break;
	case GET_HIT_STATE::STUN:
		_img = IMAGE_MANAGER->findImage("Kyoko_stun");
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setFPS(15);
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(0, 4, false, true); //
		}
		else if (player.getDirection() == DIRECTION::LEFT)
		{
			_ani->setPlayFrame(4, 8, false, true); // 
		}
		_ani->start();
		player.setIsHit(false);
		break;
	case GET_HIT_STATE::GAME_OVER:
		_img = IMAGE_MANAGER->findImage("Kyoko_gameover");
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setFPS(15);
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(0, 26, false, false); //
		}
		else if (player.getDirection() == DIRECTION::LEFT)
		{
			_ani->setPlayFrame(26, 52, false, false); // 
		}
		_ani->start();
		break;
	}
}

void getHitState::setMotalTime(Player& player)
{
	_img = IMAGE_MANAGER->findImage("Kyoko_idle");
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(20);
	if (player.getDirection() == DIRECTION::RIGHT)
	{
		_ani->setPlayFrame(0, 12, false, false); // 0 ~ 3
	}
	else if (player.getDirection() == DIRECTION::LEFT)
	{
		_ani->setPlayFrame(12, 24, false, false); // 12 ~ 15
	}
	_ani->start();
}
