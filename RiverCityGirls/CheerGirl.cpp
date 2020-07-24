#include "stdafx.h"
#include "CheerGirl.h"

void CheerGirl::init()
{
	_enemyImg = IMAGE_MANAGER->findImage("cheer_idle");
	_position = Vector3(1000, -105, 500);
	_size = Vector3(80, 210, 30);
	_state = ENEMY_STATE::IDLE;
	_direction = DIRECTION::RIGHT;
	setState(_state, _direction);

	_attackCount = 0;
	_gravity = 0;
	_jumpPower = 0;
	_hp = 100;
	_playerDistance = 0;
	_lastEnemyX = 0;
	_lastEnemyY = 0;
	_currentEnemyX = 0;
	_currentEnemyY = 0;
}

void CheerGirl::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void CheerGirl::update()
{
	Vector3 playerPos = _enemyManager->getPlayerPosition(); // 플레이어의 위치
	float distanceFromPlayer = sqrt(pow(playerPos.x - _position.x, 2) + pow(playerPos.z - _position.z, 2)); // 플레이어와 xz 거리
	Vector3 moveDir = Vector3(0, 0, 0);
	_elapsedTime += TIME_MANAGER->getElapsedTime();

	// 상태에 따른 행동 및 상태 전이
	switch (_state)
	{
	case ENEMY_STATE::IDLE: // 대기 상태
	{
		setDirectionToPlayer(); // 플레이어 바라보기

		if (_elapsedTime > 1)
		{
			if (distanceFromPlayer > 400)
			{
				setState(ENEMY_STATE::RUN, _direction); // 플레이어에게 달려가기
			}
			else
			{
				setState(ENEMY_STATE::WALK, _direction); // 플레이어에게 걸어가기
			}
		}
	}
	break;

	case ENEMY_STATE::WALK: // 걷기 상태
	{
		setDirectionToPlayer(); // 플레이어 바라보기

		_gravity += 1;
		
		moveDir.x += (_direction == DIRECTION::RIGHT) ? 1 : -1;
		moveDir.z += (playerPos.z >= _position.z + 10) ? 1 : ((playerPos.z <= _position.z - 10) ? -1 : 0);
		moveDir = Vector3::normalize(&moveDir);
		moveDir = moveDir * 2;
		moveDir.y += _gravity;

		float lastY = _position.y;
		_enemyManager->moveEnemy(this, moveDir);
		float currY = _position.y;

		if (lastY != currY) // 떨어짐
		{
			setState(ENEMY_STATE::JUMP, _direction);
		}
		else
		{
			_gravity = 0;
			if (distanceFromPlayer <= 100) // 근접 시 공격
			{
				setState(ENEMY_STATE::ATTACK, _direction);
			}
			else if (_elapsedTime >= 5) // 오랜 쫓음으로 인해 한번 점프해본다
			{
				setState(ENEMY_STATE::JUMP, _direction);
				_gravity = -22;
			}
		}
	}
	break;
	case ENEMY_STATE::RUN:
	{
		setDirectionToPlayer(); // 플레이어 바라보기

		_gravity += 1;

		moveDir.x += (_direction == DIRECTION::RIGHT) ? 1 : -1;
		moveDir.z += (playerPos.z >= _position.z + 10) ? 1 : ((playerPos.z <= _position.z - 10) ? -1 : 0);
		moveDir = Vector3::normalize(&moveDir);
		moveDir = moveDir * 4;
		moveDir.y += _gravity;

		float lastY = _position.y;
		_enemyManager->moveEnemy(this, moveDir);
		float currY = _position.y;

		if (lastY != currY) // 떨어짐
		{
			setState(ENEMY_STATE::JUMP, _direction);
		}
		else
		{
			_gravity = 0;
			if (distanceFromPlayer <= 100) // 근접 시 공격
			{
				setState(ENEMY_STATE::DASHATTACK, _direction);
			}
			else if (_elapsedTime >= 5) // 오랜 쫓음으로 인해 한번 점프해본다
			{
				setState(ENEMY_STATE::JUMP, _direction);
				_gravity = -26;
			}
		}
	}
	break;

	case ENEMY_STATE::JUMP:
	{
		_gravity += 1;
		moveDir.x += (_direction == DIRECTION::RIGHT) ? 1 : -1;
		moveDir.z += (playerPos.z >= _position.z + 10) ? 1 :((playerPos.z <= _position.z - 10)? -1 : 0);
		moveDir = Vector3::normalize(&moveDir);
		moveDir = moveDir * 2;
		moveDir.y += _gravity;

		float lastY = _position.y;
		_enemyManager->moveEnemy(this, moveDir);
		float currY = _position.y;
		
		if (_gravity > 1 && lastY == currY) // 착지한 경우
		{
			_gravity = 0;
			if (distanceFromPlayer > 400)
			{
				setState(ENEMY_STATE::RUN, _direction); // 플레이어에게 달려가기
			}
			else
			{
				setState(ENEMY_STATE::WALK, _direction); // 플레이어에게 걸어가기
			}
		}
	}
	break;

	case ENEMY_STATE::ATTACK:
	{
		if (!_ani->isPlay()) // 공격 모션이 끝났다면
		{
			setState(ENEMY_STATE::IDLE, _direction);
		}
	}
	break;

	case ENEMY_STATE::DASHATTACK:
	{
		if (!_ani->isPlay()) // 공격 모션이 끝났다면
		{
			setState(ENEMY_STATE::IDLE, _direction);
		}
	}
	break;

	case ENEMY_STATE::HIT: // 작은 경직
	{
		_gravity += 1;
		moveDir.x += (_direction == DIRECTION::RIGHT) ? -1 : 1;
		moveDir.y += _gravity;

		float lastY = _position.y;
		_enemyManager->moveEnemy(this, moveDir);
		float currY = _position.y;

		if (lastY != currY) // 떨어짐
		{
			setState(ENEMY_STATE::JUMP, _direction);
		}
		else
		{
			if (!_ani->isPlay())
			{
				setState(ENEMY_STATE::IDLE, _direction);
			}
		}
	}
	break;

	case ENEMY_STATE::KNOCKDOWN: // 쓰러지는 경직
	{
		_gravity += 1;
		moveDir.x += (_direction == DIRECTION::RIGHT) ? -1 : 1;
		moveDir.y += _gravity;

		float lastY = _position.y;
		_enemyManager->moveEnemy(this, moveDir);
		float currY = _position.y;

		if (lastY != currY) // 떨어짐
		{
		}
		else // 떨어지지 않음
		{
			_gravity = 0;
			if (_elapsedTime > 1.5f)
			{
				setState(ENEMY_STATE::STANDUP, _direction);
			}
		}
	}
	break;

	case ENEMY_STATE::STANDUP: // 쓰러지고 일어서는 상태
	{
		if (!_ani->isPlay())
		{
			setState(ENEMY_STATE::IDLE, _direction);
		}
	}
	break;

	case ENEMY_STATE::STUN: // 스턴 걸린 상태
	{
		if (_elapsedTime > 3.0f)
		{
			setState(ENEMY_STATE::IDLE, _direction);
		}
	}
	break;
	}

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());
}

void CheerGirl::render()
{
	//좌우에 따른 애니메이션 프레임 및 루프 조정
	switch (_state)
	{
	case ENEMY_STATE::IDLE:
	case ENEMY_STATE::WALK:
	case ENEMY_STATE::RUN:
	{
		if (_direction == DIRECTION::LEFT)
		{
			_ani->setPlayFrame(_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameX() * 2, false, true);
		}
		else
		{
			_ani->setPlayFrame(0, _enemyImg->getMaxFrameX(), false, true);
		}
	}
	break;
	case ENEMY_STATE::HIT:
	{
		if (_direction == DIRECTION::LEFT)
		{
			if (_hitType == ATTACK_TYPE::HIT1)
			{
				_ani->setPlayFrame(9, 12, false, false);
			}
			else if (_hitType == ATTACK_TYPE::HIT2)
			{
				_ani->setPlayFrame(12, 15, false, false);
			}
		}
		else
		{
			if (_hitType == ATTACK_TYPE::HIT1)
			{
				_ani->setPlayFrame(0, 3, false, false);
			}
			else if (_hitType == ATTACK_TYPE::HIT2)
			{
				_ani->setPlayFrame(3, 6, false, false);
			}
		}
	}
	break;
	case ENEMY_STATE::KNOCKDOWN:
	{
		if (_direction == DIRECTION::LEFT)
		{
			_ani->setPlayFrame(_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameX() * 2, false, false);
		}
		else
		{
			_ani->setPlayFrame(0, _enemyImg->getMaxFrameX(), false, false);
		}
	}
	break;
	default:
	{
		if (_direction == DIRECTION::LEFT)
		{
			_ani->setPlayFrame(_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameX() * 2, false, false);
		}
		else
		{
			_ani->setPlayFrame(0, _enemyImg->getMaxFrameX(), false, false);
		}
	}
	break;
	}

	if (DEBUG_MANAGER->isDebugMode(DEBUG_TYPE::ENEMY))
	{
		_enemyImg->setAlpha(0.5);
		FloatRect rc = FloatRect(Vector2(_position.x, _position.z + _position.y + (_size.y / 2)), Vector2(_size.x, _size.z), Pivot::Center);
		CAMERA_MANAGER->drawLine(Vector2(_position.x, _position.z), Vector2(_position.x, _position.z + _position.y));
		CAMERA_MANAGER->rectangle(rc, D2D1::ColorF::Enum::Red, 1, 1);
	}

	_enemyImg->setScale(3);
	CAMERA_MANAGER->aniRenderZ(_enemyImg, _position, _size, _ani);
}

void CheerGirl::hitEffect(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	_hitType = type;
	if (_state != ENEMY_STATE::HIT && _state != ENEMY_STATE::KNOCKDOWN && _state != ENEMY_STATE::STANDUP)
	{
		if (_hitType == ATTACK_TYPE::HIT1 || _hitType == ATTACK_TYPE::HIT2)
		{
			setState(ENEMY_STATE::HIT, _direction);

		}
		else if (_hitType == ATTACK_TYPE::KNOCKDOWN)
		{
			_gravity = -16.0f;
			setState(ENEMY_STATE::KNOCKDOWN, _direction);
		}
		else if (_hitType == ATTACK_TYPE::STUN)
		{
			setState(ENEMY_STATE::STUN, _direction);
		}
	}
}

void CheerGirl::setState(ENEMY_STATE state, DIRECTION direction)
{
	_state = state;
	_elapsedTime = 0;

	//상태에 따른 애니메이션
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
		_enemyImg = IMAGE_MANAGER->findImage("cheergirl_walk2");
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
	case ENEMY_STATE::HIT:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("cheergirl_getHit");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(8);
		_ani->start();
	}
	break;
	case ENEMY_STATE::STUN:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("cheergirl_stun");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(7);
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
		_ani->setFPS(8);
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
	}
}

void CheerGirl::setDirectionToPlayer()
{
	Vector3 playerPos = _enemyManager->getPlayerPosition();
	if (_state != ENEMY_STATE::KNOCKDOWN && _state != ENEMY_STATE::STANDUP
		&& _state != ENEMY_STATE::HIT && _state != ENEMY_STATE::STUN)
	{
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
