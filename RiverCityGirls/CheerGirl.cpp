#include "stdafx.h"
#include "CheerGirl.h"

void CheerGirl::init()
{
	_enemyImg = IMAGE_MANAGER->findImage("cheergirl_idle");
	_position = Vector3(1000, -100, 500);
	_size = Vector3(140, 200, 40);
	_state = ENEMY_STATE::IDLE;
	_direction = DIRECTION::RIGHT;
	aniPlay(_state, _direction);
	_gravity = 0;
	_jumpPower = 0;

}

void CheerGirl::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void CheerGirl::update()
{
	Vector3 playerPos = _enemyManager->getPlayerPosition();
	
	if (playerPos.x < _position.x - 200)
	{
		_direction = DIRECTION::LEFT;
	}
	else if (playerPos.x > _position.x + 200)
	{
		_direction = DIRECTION::RIGHT;
	}

	//점프력
	
	

	_playerDistance = sqrt(pow(playerPos.x - _position.x, 2) + pow(playerPos.y - _position.y, 2) + pow(playerPos.z - _position.z, 2));
	if (_state != ENEMY_STATE::JUMP && _state != ENEMY_STATE::DASHATTACK)
	{
		if (_playerDistance > 700)
		{
			if (_state != ENEMY_STATE::IDLE)
			{
				aniPlay(ENEMY_STATE::IDLE, _direction);
				_state = ENEMY_STATE::IDLE;
			}
		}
		else if (_playerDistance > 300)
		{
			if (_state != ENEMY_STATE::RUN)
			{
				aniPlay(ENEMY_STATE::RUN, _direction);
				_state = ENEMY_STATE::RUN;
			}

		}
		else if (_playerDistance <= 300 && _playerDistance > 100 && _state != ENEMY_STATE::RUN)
		{
			if (_state != ENEMY_STATE::WALK)
			{
				aniPlay(ENEMY_STATE::WALK, _direction);
				_state = ENEMY_STATE::WALK;
			}
		}
		/*else
		{
			if (_state != ENEMY_STATE::ATTACK && _attackCount <= 0)
			{
				aniPlay(ENEMY_STATE::ATTACK, _direction);
				_state = ENEMY_STATE::ATTACK;
			}
		}*/
	}
	


	Vector3 moveDir = Vector3(0, 0, 0);




	//상태 패턴에 따른 디렉션 조정
	switch (_state)
	{
	case ENEMY_STATE::IDLE:
	{
		if (_attackCount > 100)
		{
			aniPlay(ENEMY_STATE::WALK, _direction);
			_state = ENEMY_STATE::WALK;
			_attackCount = 0;
		}
		else if (_playerDistance < 100)
		{
			aniPlay(ENEMY_STATE::ATTACK, _direction);
			_state = ENEMY_STATE::ATTACK;
		}
	}
	break;
	case ENEMY_STATE::WALK:
	{
		int i = RANDOM->getFromIntTo(0,10);

		if (_direction == DIRECTION::LEFT)
		{
			moveDir.x -= 2;
		}
		else
		{
			moveDir.x += 2;
		}
		_elapsedTime++;

		if (_elapsedTime > 300)
		{
			aniPlay(ENEMY_STATE::JUMP, _direction);
			_state = ENEMY_STATE::JUMP;
			_jumpPower = 12.0f;
			_gravity = 0.3f;
			_elapsedTime = 0;
		}

		//공격
		if (_playerDistance <= 100 && _elapsedTime > 100)
		{
			if (_state != ENEMY_STATE::ATTACK)
			{
				_elapsedTime = 0;
				aniPlay(ENEMY_STATE::ATTACK, _direction);
				_state = ENEMY_STATE::ATTACK;
			}
		}
	}
	break;
	case ENEMY_STATE::RUN:
	{
		_elapsedTime++;
		if (_direction == DIRECTION::LEFT)
		{
			moveDir.x -= 4;
		}
		else
		{
			moveDir.x += 4;
		}
		if (_elapsedTime > 50 && _playerDistance <= 100)
		{
			aniPlay(ENEMY_STATE::DASHATTACK, _direction);
			_state = ENEMY_STATE::DASHATTACK;
		}
		//점프
		if (_elapsedTime > 300)
		{
			aniPlay(ENEMY_STATE::JUMP, _direction);
			_state = ENEMY_STATE::JUMP;
			_jumpPower = 12.f;
			_gravity = 0.3;
			_elapsedTime = 0;
		}

	}
	break;
	case ENEMY_STATE::JUMP:
		_position.y -= _jumpPower;
		_jumpPower -= _gravity;

		if (_direction == DIRECTION::LEFT)
		{
			moveDir.x -= 2;
		}
		else
		{
			moveDir.x += 2;
		}
		
		if (moveDir.y -100< _position.y) {
			_jumpPower = 0.0f;
			_gravity = 0.0f;
			_position.y = moveDir.y-100;
			aniPlay(ENEMY_STATE::WALK, _direction);
			_state = ENEMY_STATE::WALK;
		}
		break;
	case ENEMY_STATE::ATTACK:
	{
		_attackCount++;
		if (_attackCount % 25 == 0)
		{
			_ani->stop();
			aniPlay(ENEMY_STATE::IDLE, _direction);
			_state = ENEMY_STATE::IDLE;
			//플레이어 피격 판정
			if (_attackS <= _ani->getPlayIndex() && _ani->getPlayIndex() <= _attackE)
			{

			}
		}		
	}
	break;	
	case ENEMY_STATE::DASHATTACK:
	{
		_elapsedTime = 0;
		_dashAttackCount++;
		if (_dashAttackCount % 50 == 0)
		{
			aniPlay(ENEMY_STATE::WALK, _direction);
			_state = ENEMY_STATE::WALK;
		}
	}
	break;
	case ENEMY_STATE::SKILL:

		if (_direction == DIRECTION::LEFT)
		{
			moveDir.x -= 2;
		}
		else
		{
			moveDir.x += 2;
		}
		/*
		_attackCount++;
		if (_attackCount++ > 30)
		{
			aniPlay(ENEMY_STATE::WALK, _direction);
			_state = ENEMY_STATE::WALK;
		}
		*/

	break;
	/*case GUARD:

		break;
	case HIT:

		break;
	case DOWN:

		break;
	case STUN:

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
	if (_state != ENEMY_STATE::IDLE) {
		if (playerPos.z < _position.z - 1)
		{
			moveDir.z -= 1;
		}
		else if (playerPos.z > _position.z + 1)
		{
			moveDir.z += 1;
		}
	}
	

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());

	_enemyManager->moveEnemy(this, moveDir);
}

void CheerGirl::render()
{
	
	_enemyImg->setScale(3.f);
	//_enemyImg->FrameRender(Vector2(WINSIZEX / 2, WINSIZEY / 2), 0, 0);
	CAMERA_MANAGER->aniRenderZ(_enemyImg, _position, _size, _ani);

	//test
	char str[255];
	sprintf_s(str, "[치어리더] state : %d, jumpPower : %d", (int)_state, _jumpPower);
	TextOut(_hdc, 0, 80, str, strlen(str));
}

void CheerGirl::aniPlay(ENEMY_STATE state, DIRECTION direction)
{
	switch (state)
	{
	case ENEMY_STATE::IDLE:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("cheergirl_idle");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());

		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::WALK:
	{
		_ani = new Animation;
		int i = 2;
		char imgNameNum[128];
		sprintf_s(imgNameNum, "cheergirl_walk%d", i);
		_enemyImg = IMAGE_MANAGER->findImage(imgNameNum);
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());

		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::RUN:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("cheergirl_run");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::JUMP:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("cheergirl_jump");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(2);
		_ani->start();
	}
	break;
	case ENEMY_STATE::ATTACK:
	{
		_ani = new Animation;
		int i = RANDOM->getFromIntTo(1, 3);
		if (i == 2)
		{
			_attackS = 3;
			_attackE = 5;
		}
		else
		{
			_attackS = 3;
			_attackE = 6;
		}
		char imgNameNum[128];
		sprintf_s(imgNameNum, "cheergirl_attack%d", i);
		_enemyImg = IMAGE_MANAGER->findImage(imgNameNum);
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	
	}
	break;
	case ENEMY_STATE::DASHATTACK:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("cheergirl_attack2");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::GUARD:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("cheergirl_block");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::HIT:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("cheergirl_getHit");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::SKILL:
	{
		_ani = new Animation;
		int j = 1;
		j++;

		char imgNameNum[128];
		sprintf_s(imgNameNum, "cheergirl_jumpAttack%d", j);
		_enemyImg = IMAGE_MANAGER->findImage(imgNameNum);
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
		if (3 < j)
		{
			j = 0;

		}
	}
	break;
	}
}
