#include "stdafx.h"
#include "Boss.h"

void Boss::init()
{
	_position = Vector3(1000, -135, 500);
	_size = Vector3(180, 260, 40);
	_ani = new Animation;
	_direction = DIRECTION::LEFT;
	setState(BOSS_STATE::IDLE, _direction);

	_gravity = 0;
	_jumpPower = 0;
	_hp = 150;
	_isActive = true;
}

void Boss::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void Boss::update()
{
	Vector3 playerPos = _enemyManager->getPlayerPosition(); // 플레이어의 위치
	float distanceFromPlayer = sqrt(pow(playerPos.x - _position.x, 2) + pow(playerPos.z - _position.z, 2)); // 플레이어와 xz 거리
	Vector3 moveDir = Vector3(0, 0, 0);
	_elapsedTime += TIME_MANAGER->getElapsedTime();

	// 상태에 따른 행동 및 상태 전이
	switch (_bossState)
	{
	case BOSS_STATE::IDLE:
	{
		if (!_ani->isPlay())
		{
			setState(BOSS_STATE::WALK, _direction);
		}
	}
	break;
	case BOSS_STATE::WALK: // 걷기 상태
	{
		setDirectionToPlayer(); // 플레이어 바라보기

		moveDir.x += (_direction == DIRECTION::RIGHT) ? 1 : -1;
		moveDir.z += (playerPos.z >= _position.z + 10) ? 1 : ((playerPos.z <= _position.z - 10) ? -1 : 0);
		moveDir = Vector3::normalize(&moveDir);
		moveDir = moveDir * 3;

		_enemyManager->moveEnemy(this, moveDir);

		if (distanceFromPlayer <= 100) // 근접 시 공격이나 스킬
		{
			setAttackState(_phase);
		}
	}
	break;
	case BOSS_STATE::LAUGH:
	{
		if (!_ani->isPlay())
		{
			setState(BOSS_STATE::IDLE, _direction);
		}
	}

	// 공격 상태
	case BOSS_STATE::WEAK_PUNCH_COMBO:
	{
		if (!_ani->isPlay())
		{
			_count++;
			if (_count == 2)
			{
				_enemyImg = IMAGE_MANAGER->findImage("boss_attack2");
				_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
					_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
				_ani->setFPS(20);
				_ani->start();
			}
			else if (_count > 2)
			{
				setState(BOSS_STATE::LAUGH, _direction);
			}
			else
			{
				_enemyImg = IMAGE_MANAGER->findImage("boss_attack1");
				_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
					_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
				_ani->setFPS(20);
				_ani->start();
			}
		}
	}
	break;
	case BOSS_STATE::STRONG_PUNCH:
	{
		if (!_ani->isPlay())
		{
			setState(BOSS_STATE::LAUGH, _direction);
		}
	}
	break;
	}
	

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());
}

void Boss::render()
{
	//좌우에 따른 애니메이션 프레임 및 루프 조정
	switch (_bossState)
	{
	case BOSS_STATE::WALK:
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

	switch (_bossState) // 이미지 그리기
	{
	case BOSS_STATE::LAUGH:
	{
		Vector3 drawPos = _position;
		drawPos.y -= 35;
		CAMERA_MANAGER->aniRenderZ(_enemyImg, drawPos, _size, _ani, -(_position.y + (_size.y / 2)));
	}
	break;
	case BOSS_STATE::IDLE:
	case BOSS_STATE::WEAK_PUNCH_COMBO:
	{
		Vector3 drawPos = _position;
		drawPos.y -= 15;
		CAMERA_MANAGER->aniRenderZ(_enemyImg, drawPos, _size, _ani, -(_position.y + (_size.y / 2)));
	}
	break;
	default:
	{
		CAMERA_MANAGER->aniRenderZ(_enemyImg, _position, _size, _ani, -(_position.y + (_size.y / 2)));
	}
	break;
	}

	switch (_bossState) // 그림자 그리기
	{
	default:
	{
		CAMERA_MANAGER->drawShadowZ(_position, Vector3(180.0, _size.y, 40.0), -(_position.y + (_size.y / 2)));
	}
	break;
	}
}

void Boss::setState(BOSS_STATE state, DIRECTION direction)
{
	_bossState = state;
	_elapsedTime = 0;

	//상태에 따른 애니메이션
	switch (state)
	{
	case BOSS_STATE::IDLE:
	{
		_enemyImg = IMAGE_MANAGER->findImage("boss_idle");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(15);
		_ani->start();
	}
	break;
	case BOSS_STATE::WALK:
	{
		_enemyImg = IMAGE_MANAGER->findImage("boss_walk");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(20);
		_ani->start();
	}
	break;
	case BOSS_STATE::LAUGH:
	{
		_enemyImg = IMAGE_MANAGER->findImage("boss_laugh");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(20);
		_ani->start();
	}
	break;
	case BOSS_STATE::STRONG_PUNCH:
	{
		_enemyImg = IMAGE_MANAGER->findImage("boss_powerAttack");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(20);
		_ani->start();
	}
	break;
	case BOSS_STATE::WEAK_PUNCH_COMBO:
	{
		_count = 0;
		_enemyImg = IMAGE_MANAGER->findImage("boss_attack1");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(20);
		_ani->start();
	}
	break;


	}
}

void Boss::hitEffect(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	if (_bossState == BOSS_STATE::GET_HIT || _bossState == BOSS_STATE::GROUND_HIT) return;

	_down += damage;
	if (_bossState != BOSS_STATE::GROUND)
	{
		if (_down > 30)
		{
			_down = 0;
			setState(BOSS_STATE::KNOCKDOWN, _direction);
		}
		else
		{
			setState(BOSS_STATE::GET_HIT, _direction);
		}
	}
	else
	{
		setState(BOSS_STATE::GROUND_HIT, _direction);
	}
}

void Boss::setAttackState(BOSS_PHASE phase)
{
	switch (phase)
	{
	case BOSS_PHASE::PHASE_1:
	{
		int randomCount = RANDOM->getInt(100);
		if (randomCount < 50)
		{
			setState(BOSS_STATE::STRONG_PUNCH, _direction);
		} 
		else
		{
			setState(BOSS_STATE::WEAK_PUNCH_COMBO, _direction);
		}
	}
	break;
	}
}