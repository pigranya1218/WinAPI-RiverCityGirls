#include "stdafx.h"
#include "CheerGirl.h"

void CheerGirl::init()
{
	_enemyImg = IMAGE_MANAGER->findImage("cheer_idle");
	_position = Vector3(1000, -100, 500);
	_size = Vector3(140, 200, 40);
	_state = ENEMY_STATE::IDLE;
	_direction = DIRECTION::RIGHT;
	aniPlay(_state, _direction);
	_attackCount = 0;
	_gravity = 0;
	_jumpPower = 0;
	_hp = 100;
	_playerDistance = 0;
	_isGetHit = false;

}

void CheerGirl::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void CheerGirl::update()
{
	Vector3 playerPos = _enemyManager->getPlayerPosition();

	if (_state != ENEMY_STATE::KNOCKDOWN && _state != ENEMY_STATE::STANDUP) {
		if (playerPos.x <= _position.x - 50)
		{
			_direction = DIRECTION::LEFT;
		}
		else if (playerPos.x >= _position.x + 50)
		{
			_direction = DIRECTION::RIGHT;
		}
	}

	//점프력
	_position.y -= _jumpPower;
	_jumpPower -= _gravity;


	

	//float playerDistance = sqrt(pow(playerPos.x - _position.x, 2) + pow(playerPos.y - _position.y, 2) + pow(playerPos.z - _position.z , 2));
	_playerDistance = sqrt(pow(playerPos.x - _position.x, 2) + pow(playerPos.y - _position.y, 2) + pow(playerPos.z - _position.z, 2));
	if (_state != ENEMY_STATE::JUMP && _state != ENEMY_STATE::DASHATTACK && _state != ENEMY_STATE::KNOCKDOWN && _state != ENEMY_STATE::STANDUP)
	{
		if (_playerDistance > 700)
		{
			if (_state != ENEMY_STATE::IDLE)
			{
				aniPlay(ENEMY_STATE::IDLE, _direction);
				_state = ENEMY_STATE::IDLE;
			}
		}
		else if (_playerDistance > 500)
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
		//플레이어와의 거리가 100 이하일 경우 
		else
		{
			//피격 처리
			if (_isGetHit)
			{
				if (_state != ENEMY_STATE::HIT && _state != ENEMY_STATE::KNOCKDOWN)
				{
					if (_hitType == ATTACK_TYPE::HIT)
					{
						aniPlay(ENEMY_STATE::HIT, _direction);
						_state = ENEMY_STATE::HIT;
					}
					else
					{
						aniPlay(ENEMY_STATE::KNOCKDOWN, _direction);
						_state = ENEMY_STATE::KNOCKDOWN;
						_jumpPower = 9.0f;
						_gravity = 0.3;
					}
				}

				
			}



		}
	}

	Vector3 moveDir = Vector3(0, 0, 0);

	//플레이어의 Z축 검사
	if(_state != ENEMY_STATE::KNOCKDOWN && _state != ENEMY_STATE::STANDUP && _state != ENEMY_STATE::IDLE){
	 if (playerPos.z  >= _position.z)
	 {
		moveDir.z += 1;
	 }
	 else if (playerPos.z  <= _position.z)
	 {
		moveDir.z -= 1;
	 }
	}

	//
	//if (_state != ENEMY_STATE::ATTACK && _state != ENEMY_STATE::IDLE) _attackCount = 0;

	//상태 패턴에 따른 스테이트 조정
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
		_elapsedTime++;
		if (_direction == DIRECTION::LEFT)
		{
			moveDir.x -= 1;
		}
		else
		{
			moveDir.x += 1;
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
		else if (_playerDistance <= 100 && _state != ENEMY_STATE::ATTACK && _state != ENEMY_STATE::HIT)
		{
			aniPlay(ENEMY_STATE::GUARD, _direction);
			_state = ENEMY_STATE::GUARD;
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
	{
		if (_direction == DIRECTION::LEFT)
		{
			moveDir.x -= 2;
		}
		else
		{
			moveDir.x += 2;
		}

		//점프 후 착지했을 경우
		//if(moveDir.y > 0.5 && )
		if (-100 < _position.y)
		{
			_jumpPower = 0;
			_gravity = 0;
			_position.y = -100;
			aniPlay(ENEMY_STATE::WALK, _direction);
			_state = ENEMY_STATE::WALK;
		}
	}
	break;
	case ENEMY_STATE::ATTACK:
	{
		_attackCount++;
		/*if (!_ani->isPlay())
		{
			aniPlay(ENEMY_STATE::IDLE, _direction);
			_state = ENEMY_STATE::IDLE;
		}*/
		if (_attackCount % 25 == 0)
		{
			_ani->stop();
			aniPlay(ENEMY_STATE::IDLE, _direction);
			_state = ENEMY_STATE::IDLE;
			//플레이어 공격 판정
			//if (_attackS <= _ani->getPlayIndex() && _ani->getPlayIndex() <= _attackE)
			//{
			//	//if((playerPos.x - 50 >= _position.x)&&(playerPos.x<= _position.x+50) || ())
			//}
		}
		else if (_playerDistance > 100)
		{
			aniPlay(ENEMY_STATE::IDLE, _direction);
			_state = ENEMY_STATE::IDLE;
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
	case ENEMY_STATE::HIT:
	{
		//_direction == DIRECTION::LEFT ? _position.x += 1 : _position.x -= 1;
		_isGetHit = false;
		if (!_ani->isPlay())
		{
			aniPlay(ENEMY_STATE::IDLE, _direction);
			_state = ENEMY_STATE::IDLE;
		}
	}
	break;
	case ENEMY_STATE::KNOCKDOWN:
	{
		if (-100 < _position.y)
		{
			_jumpPower = 0;
			_gravity = 0;
			_position.y = -100;		
		}
		_isGetHit = false;
		if (_direction == DIRECTION::LEFT)
		{
			_position.x += 2;
			
		}
		else
		{
			_position.x -= 2;
			
		}
		if (_ani->isPlay())
		{
			//프레임에 따른 position.x 조정
		}
		//if (!_ani->isPlay())
		else
		{
			
			aniPlay(ENEMY_STATE::STANDUP, _direction);
			_state = ENEMY_STATE::STANDUP;
			_elapsedTime = 0;
		}
	}
	break;
	case ENEMY_STATE::STANDUP:
	{
		_elapsedTime++;
		if (_elapsedTime > 50)
		{
			_elapsedTime = 0;
			aniPlay(ENEMY_STATE::WALK, _direction);
			_state = ENEMY_STATE::WALK;
		}
		
	}
	break;
	case ENEMY_STATE::GUARD:

	break;
	/*
	case STUN:

		break;
	case SKILL:

		break;
	case HELD:

		break;*/
	}


	//좌우에 따른 애니메이션 프레임 및 루프 조정
	if (_direction == DIRECTION::LEFT)
	{
		bool loop;
		//피격 애니메이션 상태일 때
		if (_state == ENEMY_STATE::HIT)
		{
			loop = false;
			_ani->setPlayFrame(0, 2, false, loop);
		}
		else if (_state == ENEMY_STATE::KNOCKDOWN)
		{
			loop = false;
			_ani->setPlayFrame(_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameX() * 2 - 1, false, loop);
		}
		else loop = true;
		_ani->setPlayFrame(_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameX() * 2 - 1, false, loop);
	}
	else
	{
		bool loop;
		if (_state == ENEMY_STATE::HIT)
		{
			loop = false;
		}
		else if (_state == ENEMY_STATE::KNOCKDOWN)
		{
			loop = false;
			_ani->setPlayFrame(0, _enemyImg->getMaxFrameX() - 1, false, loop);
		}
		else loop = true;
		_ani->setPlayFrame(0, _enemyImg->getMaxFrameX() - 1, false, loop);
	}



	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());

	_enemyManager->moveEnemy(this, moveDir);
}

void CheerGirl::render()
{
	
	FloatRect rc = FloatRect(Vector2(_position.x, _position.z), Vector2(_size.x, _size.z), Pivot::Center);
	CAMERA_MANAGER->drawLine(Vector2(_position.x, _position.z), Vector2(_position.x, _position.z + _position.y));
	CAMERA_MANAGER->rectangle(rc, D2D1::ColorF::Enum::Red, 1, 1);

	_enemyImg->setScale(3.f);
	//_enemyImg->FrameRender(Vector2(WINSIZEX / 2, WINSIZEY / 2), 0, 0);
	CAMERA_MANAGER->aniRenderZ(_enemyImg, _position, _size, _ani);

	//test
	char str[255];
	sprintf_s(str, "[치어리더] state : %d, _elapsedTime : %f", (int)_state, _elapsedTime);
	TextOut(_hdc, 0, 80, str, strlen(str));
}

void CheerGirl::hitEffect(GameObject * hitter, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	//좌측을 바라보는
	if (hitter->getPosition().x < _position.x) _direction = DIRECTION::LEFT;
	//우측을 바라보는
	else _direction = DIRECTION::RIGHT;

	_hitType = type;
	_isGetHit = true;
}

void CheerGirl::aniPlay(ENEMY_STATE state, DIRECTION direction)
{
	//디렉션에 따른 애니메이션
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
		_enemyImg = IMAGE_MANAGER->findImage("cheergirl_walk1");
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
			_attackS = 2;
			_attackE = 4;
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
	case ENEMY_STATE::JUMPATTACK:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("cheergirl_jumpAttack2");
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
		_ani->setFPS(1);
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
	case ENEMY_STATE::STUN:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("cheergirl_stun");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::KNOCKDOWN:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("cheergirl_blownBack");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(15);
		_ani->start();
	}
	break;
	case ENEMY_STATE::STANDUP:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("cheergirl_groundUp");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::SKILL:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("cheergirl_walk2");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::HELD:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("cheergirl_getHit");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	}
}
