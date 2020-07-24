#include "stdafx.h"
#include "SchoolGirl.h"

void SchoolGirl::init()
{
	_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_idle");
	_position = Vector3(800, -100, 500);
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

	_lastEnemyX = _position.x;
	_lastEnemyY = _position.y;
}

void SchoolGirl::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void SchoolGirl::update()
{
	
	Vector3 playerPos = _enemyManager->getPlayerPosition();

	//좌우 조정
	if (_state != ENEMY_STATE::KNOCKDOWN && _state != ENEMY_STATE::HIT && _state != ENEMY_STATE::STUN
		&& _state != ENEMY_STATE::STANDUP)
	{
		if (playerPos.x <= _position.x - 60)
		{
			_direction = DIRECTION::LEFT;
		}
		else if (playerPos.x >= _position.x + 60)
		{
			_direction = DIRECTION::RIGHT;
		}
	}
	
	//점프력
	//_position.y -= _jumpPower;
	//_jumpPower -= _gravity;

	//플레이어와의 거리차를 계산해서 상태 취하기
	//float playerDistance = sqrt(pow(playerPos.x - _position.x, 2) + pow(playerPos.y - _position.y, 2) + pow(playerPos.z - _position.z , 2));
	_playerDistance = sqrt(pow(playerPos.x - _position.x, 2) + pow(playerPos.y - _position.y, 2) + pow(playerPos.z - _position.z, 2));
	if (_state != ENEMY_STATE::JUMP && _state != ENEMY_STATE::DASHATTACK && 
		_state != ENEMY_STATE::KNOCKDOWN && _state != ENEMY_STATE::STANDUP && _state != ENEMY_STATE::STUN)
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
		//플레이어와의 거리가 100 이하일 경우 
		else
		{
			//피격 처리
			if (_isGetHit)
			{
				//if (_state != ENEMY_STATE::HIT )
				//{
					if (_hitType == ATTACK_TYPE::HIT1 || _hitType == ATTACK_TYPE::HIT2)
					{
						_isGetHit = false;
						aniPlay(ENEMY_STATE::HIT, _direction);
						_state = ENEMY_STATE::HIT;
						
					}
					else if(_hitType == ATTACK_TYPE::KNOCKDOWN)
					{
						_isGetHit = false;
						_elapsedTime = 0;
						_jumpPower = 8.f;
						_gravity = 0.3f;
						aniPlay(ENEMY_STATE::KNOCKDOWN, _direction);
						_state = ENEMY_STATE::KNOCKDOWN;
					}
					else if(_hitType == ATTACK_TYPE::STUN)
					{
						_isGetHit = false;
						aniPlay(ENEMY_STATE::STUN, _direction);
						_state = ENEMY_STATE::STUN;
					}
				//}
			}
		}
	}
	
	Vector3 moveDir = Vector3(0, 0, 0);
	
	//플레이어의 Z축 검사
	if (_state == ENEMY_STATE::WALK || _state == ENEMY_STATE::RUN)
	{
		if (playerPos.z - 1 > _position.z)
		{
			moveDir.z += 1;
		}
		else if (playerPos.z + 1 < _position.z)
		{
			moveDir.z -= 1;
		}
	}
	
	//if (_state != ENEMY_STATE::ATTACK && _state != ENEMY_STATE::IDLE) _attackCount = 0;

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
		else if(_playerDistance < 100)
		{
			aniPlay(ENEMY_STATE::ATTACK, _direction);
			_state = ENEMY_STATE::ATTACK;
		}
	}
	break;
	case ENEMY_STATE::WALK:
	{
		_elapsedTime += TIME_MANAGER->getElapsedTime();
		if (_direction == DIRECTION::LEFT)
		{
			moveDir.x -= 1;
		}
		else
		{
			moveDir.x += 1;
		}
		int i = RANDOM->getFromIntTo(0, 500);
		//공격
		if (_playerDistance <= 100 && _elapsedTime > 2.f)
		{
			if (_state != ENEMY_STATE::ATTACK)
			{
				_elapsedTime = 0;
				aniPlay(ENEMY_STATE::ATTACK, _direction);
				_state = ENEMY_STATE::ATTACK;
			}
		}
		//가드
		else if (i == 250 && _playerDistance <= 100 && _state != ENEMY_STATE::ATTACK
			&& _state != ENEMY_STATE::HIT && _state != ENEMY_STATE::GUARD)
		{
			_elapsedTime = 0;
			aniPlay(ENEMY_STATE::GUARD, _direction);
			_state = ENEMY_STATE::GUARD;
		}
	}
	break;
	case ENEMY_STATE::RUN:
	{
		_elapsedTime += TIME_MANAGER->getElapsedTime();
		if (_direction == DIRECTION::LEFT)
		{
			moveDir.x -= 4;
		}
		else
		{
			moveDir.x += 4;
		}
		if (_elapsedTime > 3.f && _playerDistance <= 100)
		{
			aniPlay(ENEMY_STATE::DASHATTACK, _direction);
			_state = ENEMY_STATE::DASHATTACK;
		}
		//점프
		if (_elapsedTime > 5.f)
		{
			aniPlay(ENEMY_STATE::JUMP, _direction);
			_state = ENEMY_STATE::JUMP;
			_jumpPower = 12.f;
			_gravity = 0.3;
			//_elapsedTime = 0;
		}
	}
	break;
	case ENEMY_STATE::JUMP:
	{
		_elapsedTime = 0;
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
			//_ani->stop();
			aniPlay(ENEMY_STATE::IDLE, _direction);
			_state = ENEMY_STATE::IDLE;
			//플레이어 공격 판정
			if (_attackS <= _ani->getPlayIndex() && _ani->getPlayIndex() <= _attackE)
			{
				if (_direction == DIRECTION::RIGHT)
				{
					_attackRc = FloatRect(_position.x + 20, _position.y - 45, 
						_position.x + 130, _position.y + 10);
				}
				else
				{
					_attackRc = FloatRect(_position.x - 130, _position.y - 45,
						_position.x - 20, _position.y + 10);
				}
				_viewRc = FloatRect(_attackRc.left, _position.z + _attackRc.top,
					_attackRc.right, _position.z + _attackRc.bottom);


			}
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
		if (!_ani->isPlay())
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
		/*if (_state != ENEMY_STATE::KNOCKDOWN && _state != ENEMY_STATE::HIT && _state != ENEMY_STATE::GUARD)
		{
			_elapsedTime = 0;
			aniPlay(ENEMY_STATE::STUN, _direction);
			_state = ENEMY_STATE::STUN;
		}*/
	}
	break;
	case ENEMY_STATE::KNOCKDOWN:
	{
		//_direction == DIRECTION::LEFT ? _position.x += 1 : _position.x -= 1;
		_position.y -= _jumpPower;
		_jumpPower -= _gravity;
		if (-100 < _position.y)
		{
			_jumpPower = 0;
			_gravity = 0;
		}
		_isGetHit = false;
		_elapsedTime += TIME_MANAGER->getElapsedTime();
		if (/*_ani->isPlay() && */_elapsedTime < 1.5f)
		{
			//프레임에 따른 position.x 조정
			if (_direction == DIRECTION::LEFT)
			{
				_position.x += 2;
			}
			else
			{
				_position.x -= 2;
			}
		}
		else if (!_ani->isPlay() && _elapsedTime <= 4.f)
		{
			//플레이어에게 발로 밟히는 피격 처리

		}
		else if (!_ani->isPlay() && _elapsedTime > 4.f)
		{
			_elapsedTime = 0;
			aniPlay(ENEMY_STATE::STANDUP, _direction);
			_state = ENEMY_STATE::STANDUP;
		}
	}
	break;
	case ENEMY_STATE::STANDUP:
	{
		if (!_ani->isPlay())
		{
			aniPlay(ENEMY_STATE::IDLE, _direction);
			_state = ENEMY_STATE::IDLE;
		}
	}
	break;
	case ENEMY_STATE::GUARD:
	{
		_elapsedTime += TIME_MANAGER->getElapsedTime();
		if (_elapsedTime > 3.f)
		{
			aniPlay(ENEMY_STATE::WALK, _direction);
			_state = ENEMY_STATE::WALK;
		}
	}
	break;
	case ENEMY_STATE::STUN:
	{
		_elapsedTime += TIME_MANAGER->getElapsedTime();
		if (_isGetHit)
		{
			if (_hitType == ATTACK_TYPE::HIT1 || _hitType == ATTACK_TYPE::HIT2)
			{
				_isGetHit = false;
				aniPlay(ENEMY_STATE::HIT, _direction);
				_state = ENEMY_STATE::HIT;
				if (playerPos.x <= _position.x - 50)
				{
					_direction = DIRECTION::LEFT;
				}
				else if (playerPos.x >= _position.x + 50)
				{
					_direction = DIRECTION::RIGHT;
				}
			}
			else if (_hitType == ATTACK_TYPE::KNOCKDOWN)
			{
				_isGetHit = false;
				_elapsedTime = 0;
				aniPlay(ENEMY_STATE::KNOCKDOWN, _direction);
				_state = ENEMY_STATE::KNOCKDOWN;
				_jumpPower = 9.0f;
				_gravity = 0.3;
				_lastEnemyX = _position.x;
				_lastEnemyY = _position.y;
				if (playerPos.x <= _position.x - 50)
				{
					_direction = DIRECTION::LEFT;
				}
				else if (playerPos.x >= _position.x + 50)
				{
					_direction = DIRECTION::RIGHT;
				}
			}
		}
		if (_elapsedTime > 4.0f)
		{
			_isGetHit = false;
			_elapsedTime = 0;
			aniPlay(ENEMY_STATE::WALK, _direction);
			_state = ENEMY_STATE::WALK;
		}
	}
	break;
	/*
	case SKILL:

		break;
	case HELD:

		break;
		*/
	}

	if (_direction == DIRECTION::LEFT)
	{
		bool loop;
		//피격 애니메이션 상태일 때
		if (_state == ENEMY_STATE::HIT)
		{
			loop = false;
			if (_hitType == ATTACK_TYPE::HIT1) _ani->setPlayFrame(9, 12, false, loop);
			else if (_hitType == ATTACK_TYPE::HIT2) _ani->setPlayFrame(12, 15, false, loop);
		}
		else if (_state == ENEMY_STATE::ATTACK)
		{
			loop = false;
			_ani->setPlayFrame(_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameX() * 2, false, loop);
		}
		else if (_state == ENEMY_STATE::KNOCKDOWN)
		{
			loop = false;
			_ani->setPlayFrame(_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameX() * 2, false, loop);
		}
		else if (_state == ENEMY_STATE::STANDUP)
		{
			loop = false;
			_ani->setPlayFrame(_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameX() * 2, false, loop);
		}
		else if (_state == ENEMY_STATE::DASHATTACK)
		{
			loop = false;
			_ani->setPlayFrame(_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameX() * 2, false, loop);
		}
		else
		{
			loop = true;
			_ani->setPlayFrame(_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameX() * 2, false, loop);
		}
	}
	else // DIRECTION::RIGHT
	{
		bool loop;
		if (_state == ENEMY_STATE::HIT)
		{
			loop = false;
			if (_hitType == ATTACK_TYPE::HIT1) _ani->setPlayFrame(0, 3, false, loop);
			else if (_hitType == ATTACK_TYPE::HIT2) _ani->setPlayFrame(3, 6, false, loop);
		}
		else if (_state == ENEMY_STATE::ATTACK)
		{
			loop = false;
			_ani->setPlayFrame(0, _enemyImg->getMaxFrameX(), false, loop);
		}
		else if (_state == ENEMY_STATE::KNOCKDOWN)
		{
			loop = false;
			_ani->setPlayFrame(0, _enemyImg->getMaxFrameX(), false, loop);
		}
		else if (_state == ENEMY_STATE::STANDUP)
		{
			loop = false;
			_ani->setPlayFrame(0, _enemyImg->getMaxFrameX(), false, loop);
		}
		else if (_state == ENEMY_STATE::DASHATTACK)
		{
			loop = false;
			_ani->setPlayFrame(0, _enemyImg->getMaxFrameX(), false, loop);
		}
		else
		{
			loop = true;
			_ani->setPlayFrame(0, _enemyImg->getMaxFrameX(), false, loop);
		}
	}
	
	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());

	_enemyManager->moveEnemy(this, moveDir);

}

void SchoolGirl::render()
{
	if (DEBUG_MANAGER->isDebugMode(DEBUG_TYPE::ENEMY))
	{
		_enemyImg->setAlpha(0.5);
		FloatRect rc = FloatRect(Vector2(_position.x, _position.z), Vector2(_size.x, _size.z), Pivot::Center);
		CAMERA_MANAGER->drawLine(Vector2(_position.x, _position.z), Vector2(_position.x, _position.z + _position.y));
		CAMERA_MANAGER->rectangle(rc, D2D1::ColorF::Enum::Red, 1, 1);
	}

	_enemyImg->setScale(3.f);
	//_enemyImg->FrameRender(Vector2(WINSIZEX / 2, WINSIZEY / 2), 0, 0);
	CAMERA_MANAGER->aniRenderZ(_enemyImg, _position, _size, _ani);

	

	//test
	char str[1000];
	sprintf_s(str, "[스쿨걸] state : %d, _jumppower : %f ,_gravity : %f ", (int)_state,_jumpPower ,_gravity);
	TextOut(_hdc, 0, 40, str, strlen(str));
	sprintf_s(str, "[스쿨걸] attackCount : %d, elapsedTime : %f, isGetHit : %d", _attackCount, _elapsedTime, (int)_isGetHit);
	TextOut(_hdc, 0, 60, str, strlen(str));

	
	CAMERA_MANAGER->rectangle(_viewRc, D2D1::ColorF::Enum::Red, 1, 1);
}


void SchoolGirl::hitEffect(GameObject * hitter, FloatRect attackRc, float damage, ATTACK_TYPE type)
{

	
	////좌측을 바라보는
	//if (hitter->getPosition().x < _position.x) _direction = DIRECTION::LEFT;
	////우측을 바라보는
	//else _direction = DIRECTION::RIGHT;

	if (_state != ENEMY_STATE::GUARD)
	{
		_hitType = type;
		_isGetHit = true;
	}
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
		_ani->setFPS(2);
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
	case ENEMY_STATE::SKILL:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_skill");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::DASHATTACK:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_attack2");
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
	case ENEMY_STATE::KNOCKDOWN:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_knockDown");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::STANDUP:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_standUp");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::STUN:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_stun");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	}
}
