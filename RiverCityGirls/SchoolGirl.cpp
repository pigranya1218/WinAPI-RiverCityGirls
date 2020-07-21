#include "stdafx.h"
#include "SchoolGirl.h"

void SchoolGirl::init()
{
	_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_idle");
	_position = Vector3(1000, -100, 500);
	_size = Vector3(140, 200, 40);
	_state = ENEMY_STATE::IDLE;
	_direction = DIRECTION::RIGHT;
	aniPlay(_state, _direction);

}

void SchoolGirl::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void SchoolGirl::update()
{
	Vector3 playerPos = _enemyManager->getPlayerPosition();
	if (playerPos.x <= _position.x)
	{
		_direction = DIRECTION::LEFT;
	}
	else
	{
		_direction = DIRECTION::RIGHT;
	}



	float distance = sqrt(pow(playerPos.x - _position.x, 2) + pow(playerPos.y - _position.y, 2) + pow(playerPos.z - _position.z, 2));

	if (distance > 700)
	{
		if (_state != ENEMY_STATE::IDLE)
		{
			aniPlay(ENEMY_STATE::IDLE, _direction);
			_state = ENEMY_STATE::IDLE;
		}
	}
	else if (distance > 350)
	{
		if (_state != ENEMY_STATE::RUN)
		{
			aniPlay(ENEMY_STATE::RUN, _direction);
			_state = ENEMY_STATE::RUN;
		}

	}
	else if (distance > 100)
	{
		if (_state != ENEMY_STATE::WALK)
		{
			aniPlay(ENEMY_STATE::WALK, _direction);
			_state = ENEMY_STATE::WALK;
		}

	}
	else
	{
		if (_state != ENEMY_STATE::ATTACK)
		{
			aniPlay(ENEMY_STATE::ATTACK, _direction);
			_state = ENEMY_STATE::ATTACK;
		}
	}


	Vector3 moveDir = Vector3(0, 0, 0);




	//상태 패턴에 따른 디렉션 조정
	switch (_state)
	{
	case ENEMY_STATE::IDLE:
	{
	}
	break;
	case ENEMY_STATE::WALK:
	{
		if (_direction == DIRECTION::LEFT)
		{
			moveDir.x -= 1;
		}
		else
		{
			moveDir.x += 1;
		}
		//점프 테스트하기위해 카운트로 만들었음
		_elapsedTime++;
		if (_elapsedTime > 150)
		{

			_state = ENEMY_STATE::JUMP;
			_jumpPower = 11.0f;
			_gravity = 0.3f;
			_elapsedTime = 0;

		}



	}
	break;
	case ENEMY_STATE::RUN:
	{
		if (_direction == DIRECTION::LEFT)
		{
			moveDir.x -= 4;
		}
		else
		{
			moveDir.x += 4;
		}


	}
	break;
	case ENEMY_STATE::JUMP:





		break;
	case ENEMY_STATE::ATTACK:
	{
		if (!_ani->isPlay())
		{
			aniPlay(ENEMY_STATE::IDLE, _direction);
			_state = ENEMY_STATE::IDLE;
		}
		else
		{
			if (_attackS <= _ani->getPlayIndex() && _ani->getPlayIndex() <= _attackE)
			{

			}
		}
	}
	break;
	/*case GUARD:

		break;
	case HIT:

		break;
	case DOWN:

		break;
	case STUN:

		break;
	case SKILL:

		break;
	case HELD:

		break;*/
	}

	if (_direction == DIRECTION::LEFT)
	{
		_ani->setPlayFrame(_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameX() * 2 - 1, false, true);
	}
	else
	{
		_ani->setPlayFrame(0, _enemyImg->getMaxFrameX() - 1, false, true);
	}
	//항상 플레이어 z축따라감
	if (playerPos.z < _position.z)
	{
		moveDir.z -= 1;
	}
	else if (playerPos.z > _position.z)
	{
		moveDir.z += 1;
	}



	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());

	_enemyManager->moveEnemy(this, moveDir);
}

void SchoolGirl::render()
{
	
	_enemyImg->setScale(3.f);
	//_enemyImg->FrameRender(Vector2(WINSIZEX / 2, WINSIZEY / 2), 0, 0);
	CAMERA_MANAGER->aniRenderZ(_enemyImg, _position, _size, _ani, true);
	
}

void SchoolGirl::aniPlay(ENEMY_STATE state, DIRECTION direction)
{
	switch (state)
	{
	case ENEMY_STATE::IDLE:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_idle");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());

		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::WALK:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_walk");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());

		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::RUN:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_run");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::JUMP:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_jump");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::ATTACK:
	{
		_ani = new Animation;
		int i = RANDOM->getFromIntTo(1, 4);
		if (i == 3)
		{
			_attackS = 3;
			_attackE = 5;
		}
		else
		{
			_attackS = 2;
			_attackE = 4;
		}
		char imgNameNum[128];
		sprintf_s(imgNameNum, "schoolgirl_attack%d", i);
		_enemyImg = IMAGE_MANAGER->findImage(imgNameNum);
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::GUARD:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_block");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::HIT:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_getHit");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	}
}
