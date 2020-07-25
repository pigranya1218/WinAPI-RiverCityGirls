#include "stdafx.h"
#include "Boss.h"

void Boss::init()
{
	_position = Vector3(1000, -135, 500);
	_size = Vector3(180, 260, 40);
	_ani = new Animation;
	_direction = DIRECTION::LEFT;
	setState(BOSS_STATE::IDLE, _direction, true);

	_gravity = 0;
	_jumpPower = 0;
	_maxHp = 300;
	_hp = _maxHp;
	_isActive = true;
}

void Boss::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void Boss::update()
{
	_enemyManager->setBossUiVisible(true);
	_enemyManager->setBossUi(_hp, _maxHp);

	if (_phase == BOSS_PHASE::DEFEAT)
	{
		if (!_ani->isPlay())
		{
			if (_direction == DIRECTION::LEFT)
			{
				_ani->setPlayFrame(_enemyImg->getMaxFrameX() + 10, _enemyImg->getMaxFrameX() + 13, false, true);
			}
			else
			{
				_ani->setPlayFrame(10, 13, false, true);
			}
			_ani->start();
		}
	}
	else
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
				setState(BOSS_STATE::WALK, _direction, true);
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
				setState(BOSS_STATE::IDLE, _direction, true);
			}
		}
		break;
		case BOSS_STATE::GET_HIT:
		{
			setDirectionToPlayer(); // 플레이어 바라보기

			moveDir.x += (_direction == DIRECTION::RIGHT) ? -0.5 : 0.5;
			moveDir = moveDir * 3;

			_enemyManager->moveEnemy(this, moveDir);

			if (!_ani->isPlay())
			{
				_combo++;
				setState(BOSS_STATE::IDLE, _direction, true);
			}
		}
		break;
		case BOSS_STATE::GROUND_HIT:
		{
			setDirectionToPlayer(); // 플레이어 바라보기

			_gravity += 0.5;
			_jumpPower += _gravity;
			moveDir.y += _jumpPower;

			float lastY = _position.y;
			_enemyManager->moveEnemy(this, moveDir);
			float currY = _position.y;


			if (!_ani->isPlay())
			{
				_combo++;
				_gravity = 0;
				setState(BOSS_STATE::GROUND, _direction, false);
			}
		}
		break;
		case BOSS_STATE::KNOCKDOWN:
		{
			_gravity += 0.5;
			_jumpPower += _gravity;
			if (_gravity != 0.5)
			{
				moveDir.x += (_direction == DIRECTION::RIGHT) ? -3 : 3;
			}
			moveDir.y += _jumpPower;

			float lastY = _position.y;
			_enemyManager->moveEnemy(this, moveDir);
			float currY = _position.y;

			if (!_ani->isPlay())
			{
				if (_hp == 0)
				{
					_phase = BOSS_PHASE::DEFEAT;
					_enemyImg = IMAGE_MANAGER->findImage("boss_defeat");
					_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(), _enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
					_ani->setFPS(15);
					if (_direction == DIRECTION::LEFT)
					{
						_ani->setPlayFrame(_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameX() * 2, false, false);
					}
					else
					{
						_ani->setPlayFrame(0, _enemyImg->getMaxFrameX(), false, false);
					}
					_ani->start();
				}
				else
				{
					setState(BOSS_STATE::GROUND, _direction, true);
				}
			}
			else if (moveDir.y >= 1 && lastY == currY) // 땅에 부딪힘
			{
				_gravity = 0;
				if (_count == 0)
				{
					_count++;
					_jumpPower = -20;
				}
				else if (_count == 1)
				{
					_count++;
					_jumpPower = -10;
				}
			}
		}
		break;

		case BOSS_STATE::GROUND:
		{
			if (_elapsedTime > 2)
			{
				setState(BOSS_STATE::STAND_UP, _direction, true);
			}
		}
		break;

		case BOSS_STATE::METEOR_ATTACK_DELAY:
		{
			if (!_ani->isPlay())
			{
				setState(BOSS_STATE::IDLE, _direction, false);
			}
		}
		break;

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
					_ani->setFPS(30);
					_ani->start();
				}
				else if (_count > 2)
				{
					setState(BOSS_STATE::LAUGH, _direction, true);
				}
				else
				{
					_enemyImg = IMAGE_MANAGER->findImage("boss_attack1");
					_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
						_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
					_ani->setFPS(30);
					_ani->start();
				}
			}
		}
		break;

		case BOSS_STATE::STRONG_PUNCH:
		{
			if (!_ani->isPlay())
			{
				setState(BOSS_STATE::LAUGH, _direction, true);
			}
		}
		break;

		case BOSS_STATE::STAND_UP:
		{
			if (!_ani->isPlay())
			{
				if (_phase == BOSS_PHASE::PHASE_1 && _hp == 200)
				{
					setState(BOSS_STATE::ROAR, _direction, true);
					_phase = BOSS_PHASE::PHASE_2;
				}
				else if (_phase == BOSS_PHASE::PHASE_2 && _hp == 100)
				{
					setState(BOSS_STATE::ROAR, _direction, true);
					_phase = BOSS_PHASE::PHASE_3;
				}
				else
				{
					setState(BOSS_STATE::IDLE, _direction, true);
				}
			}
		}
		break;

		case BOSS_STATE::ROAR:
		{
			if (!_ani->isPlay())
			{
				setState(BOSS_STATE::IDLE, _direction, true);
			}
		}
		break;

		case BOSS_STATE::METEOR_ATTACK:
		{
			if (_count == 0)
			{
				if (_ani->getPlayIndex() >= 6)
				{
					moveDir.y += _jumpPower;

					_enemyManager->moveEnemy(this, moveDir);

					if (_position.y <= -2000)
					{
						_count++;
						_elapsedTime = 0;
					}
				}
			}
			else if (_count == 1) // 플레이어와 근접한 방향으로 이동
			{
				setDirectionToPlayer();

				moveDir.x += (_direction == DIRECTION::RIGHT) ? 1 : -1;
				moveDir.z += (playerPos.z >= _position.z + 10) ? 1 : ((playerPos.z <= _position.z - 10) ? -1 : 0);
				moveDir = Vector3::normalize(&moveDir);
				moveDir = moveDir * 8;

				_enemyManager->moveEnemy(this, moveDir);

				if (_elapsedTime > 2)
				{
					_count++;
					_enemyImg = IMAGE_MANAGER->findImage("boss_falling");
					_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
						_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
					_ani->setFPS(15);
					_ani->start();
				}
				
			}
			else // 떨어지기 
			{
				moveDir.y -= _jumpPower;

				float lastY = _position.y;
				_enemyManager->moveEnemy(this, moveDir);
				float currY = _position.y;

				if (moveDir.y >= 1 && lastY == currY) // 땅에 부딪힘
				{
					_gravity = 0;
					_jumpPower = 0;
					setState(BOSS_STATE::METEOR_ATTACK_DELAY, _direction, true);
				}
			}
		}
		break;
		}
	}

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());
}

void Boss::render()
{
	//좌우에 따른 애니메이션 프레임 및 루프 조정
	if (_phase != BOSS_PHASE::DEFEAT)
	{
		switch (_bossState)
		{
		case BOSS_STATE::WALK:
		case BOSS_STATE::GROUND:
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
		case BOSS_STATE::GET_HIT:
		{
			if (_direction == DIRECTION::LEFT)
			{
				_ani->setPlayFrame(_enemyImg->getMaxFrameX() + 3 * _combo, _enemyImg->getMaxFrameX() + 3 * _combo + 1, false, false);
			}
			else
			{
				_ani->setPlayFrame(3 * _combo, 3 * _combo + 1, false, false);
			}
		}
		break;
		case BOSS_STATE::METEOR_ATTACK:
		{
			if (_count == 0)
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
			else if (_count == 2)
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
	}
	

	if (DEBUG_MANAGER->isDebugMode(DEBUG_TYPE::ENEMY))
	{
		_enemyImg->setAlpha(0.5);
		FloatRect rc = FloatRect(Vector2(_position.x, _position.z + _position.y + (_size.y / 2)), Vector2(_size.x, _size.z), Pivot::Center);
		CAMERA_MANAGER->drawLine(Vector2(_position.x, _position.z), Vector2(_position.x, _position.z + _position.y));
		CAMERA_MANAGER->rectangle(rc, D2D1::ColorF::Enum::Red, 1, 1);
	}

	_enemyImg->setScale(3);

	if (_phase == BOSS_PHASE::DEFEAT)
	{
		Vector3 drawPos = _position;
		drawPos.y -= 20;
		CAMERA_MANAGER->aniRenderZ(_enemyImg, drawPos, _size, _ani, -(_position.y + (_size.y / 2)));
	}
	else
	{
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
		{
			Vector3 drawPos = _position;
			drawPos.y -= 20;
			CAMERA_MANAGER->aniRenderZ(_enemyImg, drawPos, _size, _ani, -(_position.y + (_size.y / 2)));
		}
		break;
		case BOSS_STATE::WEAK_PUNCH_COMBO:
		{
			if (_count == 2)
			{
				Vector3 drawPos = _position;
				drawPos.y -= 15;
				CAMERA_MANAGER->aniRenderZ(_enemyImg, drawPos, _size, _ani, -(_position.y + (_size.y / 2)));
			}
			else
			{
				Vector3 drawPos = _position;
				drawPos.y -= 20;
				CAMERA_MANAGER->aniRenderZ(_enemyImg, drawPos, _size, _ani, -(_position.y + (_size.y / 2)));
			}
		}
		break;
		case BOSS_STATE::GROUND:
		case BOSS_STATE::GROUND_HIT:
		case BOSS_STATE::STAND_UP:
		case BOSS_STATE::ROAR:
		case BOSS_STATE::GET_HIT:
		case BOSS_STATE::METEOR_ATTACK:
		case BOSS_STATE::METEOR_ATTACK_DELAY:
		{
			Vector3 drawPos = _position;
			drawPos.y -= 20;
			CAMERA_MANAGER->aniRenderZ(_enemyImg, drawPos, _size, _ani, -(_position.y + (_size.y / 2)));
		}
		break;
		default:
		{
			CAMERA_MANAGER->aniRenderZ(_enemyImg, _position, _size, _ani, -(_position.y + (_size.y / 2)));
		}
		break;
		}
	}
	

	switch (_bossState) // 그림자 그리기
	{
	case BOSS_STATE::METEOR_ATTACK:
	{
		Vector3 shadowPos = _position;
		shadowPos.y = _enemyManager->getCenterBottom(_position);
		CAMERA_MANAGER->drawShadowZ(shadowPos, Vector3(180.0, 0, 40.0), -shadowPos.y);
	}
	break;
	default:
	{
		CAMERA_MANAGER->drawShadowZ(_position, Vector3(180.0, _size.y, 40.0), -(_position.y + (_size.y / 2)));
	}
	break;
	}
}

void Boss::setState(BOSS_STATE state, DIRECTION direction, bool initTime)
{
	_bossState = state;
	if (initTime)
	{
		_elapsedTime = 0;
	}

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
		_ani->setFPS(30);
		_ani->start();
	}
	break;
	case BOSS_STATE::GET_HIT:
	{
		_enemyImg = IMAGE_MANAGER->findImage("boss_getHit");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case BOSS_STATE::GROUND_HIT:
	{
		_enemyImg = IMAGE_MANAGER->findImage("boss_groundHit");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case BOSS_STATE::KNOCKDOWN:
	{
		_count = 0;
		_enemyImg = IMAGE_MANAGER->findImage("boss_blownBack");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(15);
		_ani->start();
	}
	break;
	case BOSS_STATE::GROUND:
	{
		_enemyImg = IMAGE_MANAGER->findImage("boss_dizzy");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case BOSS_STATE::STAND_UP:
	{
		_enemyImg = IMAGE_MANAGER->findImage("boss_getup");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(15);
		_ani->start();
	}
	break;
	case BOSS_STATE::ROAR:
	{
		_enemyImg = IMAGE_MANAGER->findImage("boss_roar");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(15);
		_ani->start();
	}
	break;
	case BOSS_STATE::METEOR_ATTACK:
	{
		_count = 0;
		_enemyImg = IMAGE_MANAGER->findImage("boss_jump");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(15);
		_ani->start();
	}
	break;
	case BOSS_STATE::METEOR_ATTACK_DELAY:
	{
		_enemyImg = IMAGE_MANAGER->findImage("boss_fallingmiss");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	}
}

void Boss::hitEffect(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	if (_bossState == BOSS_STATE::GET_HIT || _bossState == BOSS_STATE::GROUND_HIT) return;

	if (_phase == BOSS_PHASE::PHASE_1)
	{
		_hp = max(200, _hp - damage);
	}
	else if (_phase == BOSS_PHASE::PHASE_2)
	{
		_hp = max(100, _hp - damage);
	}
	else if (_phase == BOSS_PHASE::PHASE_3)
	{
		_hp = max(0, _hp - damage);
	}

	if (_bossState == BOSS_STATE::IDLE || _bossState == BOSS_STATE::WALK || _bossState == BOSS_STATE::LAUGH) // 빈틈
	{
		if (_combo > 2 || type == ATTACK_TYPE::KNOCKDOWN)
		{
			_combo = 0;
			setState(BOSS_STATE::KNOCKDOWN, _direction, true);
		}
		else
		{
			_jumpPower = -30;
			setState(BOSS_STATE::GET_HIT, _direction, true);
		}
	}
	if (_bossState == BOSS_STATE::GROUND)
	{
		_jumpPower = -10;
		setState(BOSS_STATE::GROUND_HIT, _direction, false);
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
			setState(BOSS_STATE::STRONG_PUNCH, _direction, true);
		} 
		else
		{
			setState(BOSS_STATE::WEAK_PUNCH_COMBO, _direction, true);
		}
	}
	break;
	case BOSS_PHASE::PHASE_2:
	{
		int randomCount = RANDOM->getInt(100);
		if (randomCount < 10) // 10%
		{
			setState(BOSS_STATE::STRONG_PUNCH, _direction, true);
		}
		else if (randomCount < 20) // 10%
		{
			setState(BOSS_STATE::WEAK_PUNCH_COMBO, _direction, true);
		}
		else if (randomCount < 60) // 40%
		{
			_jumpPower = -50;
			setState(BOSS_STATE::METEOR_ATTACK, _direction, true);
		}
		else // 40%
		{
			_jumpPower = -50;
			setState(BOSS_STATE::METEOR_ATTACK, _direction, true);
		}
	}
	break;
	case BOSS_PHASE::PHASE_3:
	{
		int randomCount = RANDOM->getInt(100);
		if (randomCount < 50)
		{
			setState(BOSS_STATE::STRONG_PUNCH, _direction, true);
		}
		else
		{
			setState(BOSS_STATE::WEAK_PUNCH_COMBO, _direction, true);
		}
	}
	break;
	}
}