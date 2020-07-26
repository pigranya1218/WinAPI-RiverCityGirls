#include "stdafx.h"
#include "schoolBoy.h"

void SchoolBoy::init()
{
	//_enemyImg = IMAGE_MANAGER->findImage("school_idle");
	_position = Vector3(600, -105, 500);
	_size = Vector3(140, 200, 40);
	_state = ENEMY_STATE::IDLE;
	_direction = DIRECTION::RIGHT;
	_ani = new Animation;
	setState(_state, _direction);
	_hitCount = 0;
	_attackCount = 0;
	_gravity = 0;
	_jumpPower = 0;
	_hp = 100;
	_isActive = true;
	_isAttack = false;
}

void SchoolBoy::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void SchoolBoy::update()
{
	_attackRc = FloatRect(0, 0, 0, 0);
	_viewRc = FloatRect(0, 0, 0, 0);

	Vector3 playerPos = _enemyManager->getPlayerPosition(); //플레이어 위치
	float distanceFromPlayer = sqrt(pow(playerPos.x - _position.x, 2) + pow(playerPos.z - _position.z, 2)); // 플레이어와 xz 거리
	Vector3 moveDir = Vector3(0, 0, 0);
	_elapsedTime += TIME_MANAGER->getElapsedTime();

	// 적 개체의 HP가 0이하
	if (_hp <= 0 && _state != ENEMY_STATE::KNOCKDOWN)
	{
		setState(ENEMY_STATE::KNOCKDOWN, _direction);
	}

	//피격 카운트 초기화
	if (_elapsedTime > 1.5)
	{
		_hitCount = 0;
	}

	//공격 카운트 초기화
	if (_elapsedTime > 1.5)
	{
		_attackCount = 0;
	}

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
			else //if(distanceFromPlayer > 100)
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
			if (distanceFromPlayer <= 200 && _elapsedTime > 1) // 모래 뿌리기
			{
				setState(ENEMY_STATE::SKILL, _direction);
			}
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
			//오브젝트 사이에 충돌
			

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
	case ENEMY_STATE::RETURN:
	{
		moveDir.z += (playerPos.z < _position.z) ? 1 : ((playerPos.z > _position.z) ? -1 : 0);
		moveDir.x += (_direction == DIRECTION::RIGHT) ? 1 : -1;
		moveDir = Vector3::normalize(&moveDir);
		moveDir = moveDir * 1;
		_enemyManager->moveEnemy(this, moveDir);

		if (_elapsedTime > 1.5)
		{
			_elapsedTime = 0;
			setState(ENEMY_STATE::WALK, _direction);

			if (distanceFromPlayer > 400)
			{
				setState(ENEMY_STATE::RUN, _direction); // 플레이어에게 달려가기
			}
		}
	}
	break;

	case ENEMY_STATE::JUMP:
	{
		_gravity += 1;
		moveDir.x += (_direction == DIRECTION::RIGHT) ? 1 : -1;
		moveDir.z += (playerPos.z >= _position.z + 10) ? 1 : ((playerPos.z <= _position.z - 10) ? -1 : 0);
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
			if (_attackCount < 100) setState(ENEMY_STATE::ATTACK, _direction);
			else
			{
				_attackCount = 0;
				setState(ENEMY_STATE::IDLE, _direction);
			}
		}
		else
		{
			if (_direction == DIRECTION::LEFT && _ani->getPlayIndex() == _attackS)
			{
				_attackRc = FloatRect(_position.x - 130, _position.y - 35,
					_position.x - 20, _position.y + 20);
			}
			else if (_direction == DIRECTION::RIGHT && _ani->getPlayIndex() == _attackS)
			{
				_attackRc = FloatRect(_position.x + 20, _position.y - 35,
					_position.x + 100, _position.y + 20);
			}
			else
			{
				_attackRc = FloatRect(0, 0, 0, 0);
				_viewRc = FloatRect(0, 0, 0, 0);
			}
			_viewRc = FloatRect(_attackRc.left, _position.z + _attackRc.top,
				_attackRc.right, _position.z + _attackRc.bottom);
			ATTACK_TYPE type;
			if (_attackCount > 0 && _attackCount % 100 == 0)
			{
				type = ATTACK_TYPE::KNOCKDOWN;
			} 
			else
			{
				type = ATTACK_TYPE::HIT1;
				_attackCount += 1;
			}
			enemyAttack(_position, _size, OBJECT_TEAM::ENEMY, _attackRc, 5, type);
		}
	}
	break;

	case ENEMY_STATE::DASHATTACK:
	{
		if (!_ani->isPlay()) // 공격 모션이 끝났다면
		{
			setState(ENEMY_STATE::IDLE, _direction);
		}
		else
		{
			if (_direction == DIRECTION::LEFT && _ani->getPlayIndex() == _attackS)
			{
				_attackRc = FloatRect(_position.x - 130, _position.y - 35,
					_position.x - 20, _position.y + 20);
			}
			else if (_direction == DIRECTION::RIGHT && _ani->getPlayIndex() == _attackS)
			{
				_attackRc = FloatRect(_position.x + 20, _position.y - 35,
					_position.x + 100, _position.y + 20);
			}
			else
			{
				_attackRc = FloatRect(0, 0, 0, 0);
				_viewRc = FloatRect(0, 0, 0, 0);
			}
			_viewRc = FloatRect(_attackRc.left, _position.z + _attackRc.top,
				_attackRc.right, _position.z + _attackRc.bottom);
			enemyAttack(_position, _size, OBJECT_TEAM::ENEMY, _attackRc, 5, ATTACK_TYPE::HIT2);
		}
	}
	break;
	case ENEMY_STATE::SKILL:
	{
		setDirectionToPlayer(); // 플레이어 바라보기

		moveDir.x += (_direction == DIRECTION::RIGHT) ? 1 : -1;
		moveDir.z += (playerPos.z >= _position.z + 10) ? 1 : ((playerPos.z <= _position.z - 10) ? -1 : 0);
		moveDir = Vector3::normalize(&moveDir);
		moveDir = moveDir * 2;

		if (!_ani->isPlay()) // 공격 모션이 끝났다면
		{
			setState(ENEMY_STATE::IDLE, _direction);
		}
		else
		{
			if (_direction == DIRECTION::LEFT && _ani->getPlayIndex() == _attackS)
			{
				_attackRc = FloatRect(_position.x - 300, _position.y - 45,
					_position.x - 100, _position.y + 20);
			}
			else if (_direction == DIRECTION::RIGHT && _ani->getPlayIndex() == _attackS)
			{
				_attackRc = FloatRect(_position.x + 100, _position.y - 45,
					_position.x + 300, _position.y + 20);
			}
			else
			{
				_attackRc = FloatRect(0, 0, 0, 0);
				_viewRc = FloatRect(0, 0, 0, 0);
			}
			_viewRc = FloatRect(_attackRc.left, _position.z + _attackRc.top,
				_attackRc.right, _position.z + _attackRc.bottom);
			enemyAttack(_position, _size, OBJECT_TEAM::ENEMY, _attackRc, 5, ATTACK_TYPE::HIT1);
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
		_hitCount += 1;
		if (lastY != currY) // 떨어지는 중
		{
			setState(ENEMY_STATE::JUMP, _direction);
		}
		else
		{
			if (!_ani->isPlay())
			{
				setState(ENEMY_STATE::IDLE, _direction);
			}
			_hitCount += 1;
			if (_hitCount > 100)
			{
				_hitCount = 0;
				_gravity = -16.0f;
				setState(ENEMY_STATE::KNOCKDOWN, _direction);
			}
		}
	}
	break;

	case ENEMY_STATE::KNOCKDOWN: // 쓰러지는 경직
	{
		_gravity += 1;
		if (_gravity != 1)
		{
			moveDir.x += (_direction == DIRECTION::RIGHT) ? -2 : 2;
		}
		moveDir.y += _gravity;

		float lastY = _position.y;
		_enemyManager->moveEnemy(this, moveDir);
		float currY = _position.y;

		if (moveDir.y > 1 && lastY == currY) // 땅에 부딪힘
		{
			_gravity = 0;
			
			if (_elapsedTime > 3 && _hp > 0)
			{
				setState(ENEMY_STATE::STANDUP, _direction);
			}
			else if (_hp <= 0 && !_ani->isPlay())
			{
				_isActive = false;
			}
		}
		/*else
		{
			_elapsedTime = 0;
		}*/
	}
	break;

	case ENEMY_STATE::STANDUP: // 쓰러지고 일어서는 상태
	{
		if (!_ani->isPlay())
		{
			int stunRate = RANDOM->getInt(3);
			if (stunRate == 2 && _hp <= 60) setState(ENEMY_STATE::STUN, _direction);
			else setState(ENEMY_STATE::IDLE, _direction);
		}
	}
	break;

	case ENEMY_STATE::STUN: // 스턴 걸린 상태
	{
		if (_elapsedTime > 5.0f)
		{
			setState(ENEMY_STATE::IDLE, _direction);
		}
	}
	break;
	}

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());
}

void SchoolBoy::render()
{
	//좌우에 따른 애니메이션 프레임 및 루프 조정
	switch (_state)
	{
	case ENEMY_STATE::IDLE:
	case ENEMY_STATE::WALK:
	case ENEMY_STATE::RUN:
	case ENEMY_STATE::STUN:
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
		FloatRect rc = FloatRect(Vector2(_position.x, _position.z), Vector2(_size.x, _size.z), Pivot::Center);
		CAMERA_MANAGER->drawLine(Vector2(_position.x, _position.z), Vector2(_position.x, _position.z + _position.y));
		CAMERA_MANAGER->rectangle(rc, D2D1::ColorF::Enum::Red, 1, 1);
		CAMERA_MANAGER->rectangle(_viewRc, D2D1::ColorF::Enum::Magenta, 1, 1);

		//test
		char str[255];
		sprintf_s(str, "[스쿨보이] state : %d, jumpPower : %d, gravity : %d", (int)_state, _jumpPower, _gravity);
		TextOut(_hdc, 500, 0, str, strlen(str));

		sprintf_s(str, "[스쿨보이] elapsedTime : %f, hitCount : %f, attackCount : %d", _elapsedTime, _hitCount, _attackCount);
		TextOut(_hdc, 500, 20, str, strlen(str));
	}

	_enemyImg->setScale(3.f);
	//CAMERA_MANAGER->aniRenderZ(_enemyImg, _position, _size, _ani);
	//이미지 그리기
	switch (_state)
	{
	case ENEMY_STATE::IDLE:
	{
		Vector3 drawPos = _position;
		//drawPos.y -= 4;
		CAMERA_MANAGER->aniRenderZ(_enemyImg, drawPos, _size, _ani, -(_position.y + (_size.y / 2)));
	}
	break;
	case ENEMY_STATE::WALK:
	case ENEMY_STATE::RUN:
	{
		Vector3 drawPos = _position;
		drawPos.y += 1;
		CAMERA_MANAGER->aniRenderZ(_enemyImg, drawPos, _size, _ani, -(_position.y + (_size.y / 2)));
	}
	break;
	case ENEMY_STATE::ATTACK:
	{
		Vector3 drawPos = _position;
		//if (_enemyImg == IMAGE_MANAGER->findImage("schoolboy_attack1")) _drawYFix = 0;
		//else if (_enemyImg == IMAGE_MANAGER->findImage("schoolboy_attack2")) _drawYFix = -3;
		//else if (_enemyImg == IMAGE_MANAGER->findImage("schoolboy_attack3")) _drawYFix = -10;
		drawPos.y -= 5;
		CAMERA_MANAGER->aniRenderZ(_enemyImg, drawPos, _size, _ani, -(_position.y + (_size.y / 2)));
	}
	break;
	case ENEMY_STATE::DASHATTACK:
	case ENEMY_STATE::GUARD:
	case ENEMY_STATE::HIT:
	case ENEMY_STATE::KNOCKDOWN: //사망 처리
	{
		if (_hp <= 0 && _ani->isPlay())
		{
			if (fmod(_elapsedTime, 0.2f) < 0.1f)
			{
				_enemyImg->setAlpha(1);
			}
			else if(fmod(_elapsedTime, 0.2f) >= 0.1f)
			{
				_enemyImg->setAlpha(0);
			}
			Vector3 drowPos = _position;
			drowPos.y = _position.y + 30;
			CAMERA_MANAGER->aniRenderZ(_enemyImg, drowPos, _size, _ani, -(_position.y + (_size.y / 2)));
		}
		else
		{
			Vector3 drowPos = _position;
			drowPos.y = _position.y + 30;
			CAMERA_MANAGER->aniRenderZ(_enemyImg, drowPos, _size, _ani, -(_position.y + (_size.y / 2)));
		}
	}
	break;
	case ENEMY_STATE::STANDUP:
	{
		if (_hp > 0)
		{
			Vector3 drawPos = _position;
			drawPos.y += 10;
			CAMERA_MANAGER->aniRenderZ(_enemyImg, drawPos, _size, _ani, -(_position.y + (_size.y / 2)));
		}
		else _isActive = false;
	}
	break;
	default:
	{
		CAMERA_MANAGER->aniRenderZ(_enemyImg, _position, _size, _ani, -(_position.y + (_size.y / 2)));
	}
		break;
	}

	
	

	//그림자 그리기
	switch (_state)
	{
	case ENEMY_STATE::JUMP:
	case ENEMY_STATE::JUMPATTACK:
	case ENEMY_STATE::KNOCKDOWN:
	{
		Vector3 shadowPos = _position;
		shadowPos.y = _enemyManager->getCenterBottom(_position);
		CAMERA_MANAGER->drawShadowZ(shadowPos, Vector3(120.0, 0, 25.0), -shadowPos.y);
	}
	break;
	default:
	{
		CAMERA_MANAGER->drawShadowZ(_position, Vector3(120.0, _size.y, 25.0), -(_position.y + (_size.y / 2)));
	}
	break;
	}

	
}

//피격
void SchoolBoy::hitEffect(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type)
{

	_hitType = type;
	if (_state != ENEMY_STATE::HIT && _state != ENEMY_STATE::KNOCKDOWN && _state != ENEMY_STATE::STANDUP)
	{
		if (_hitType == ATTACK_TYPE::HIT1 || _hitType == ATTACK_TYPE::HIT2)
		{
			_hp -= damage;
			setState(ENEMY_STATE::HIT, _direction);
		}
		else if (_hitType == ATTACK_TYPE::KNOCKDOWN)
		{
			_gravity = -16.0f;
			_hp -= damage;
			setState(ENEMY_STATE::KNOCKDOWN, _direction);
		}
		else if (_hitType == ATTACK_TYPE::STUN)
		{
			_hp -= damage;
			setState(ENEMY_STATE::STUN, _direction);
		}
	}
}


void SchoolBoy::setState(ENEMY_STATE state, DIRECTION direction)
{
	_state = state;
	_elapsedTime = 0;

	//디렉션에 따른 애니메이션
	switch (state)
	{
	case ENEMY_STATE::IDLE:
	{
		_enemyImg = IMAGE_MANAGER->findImage("schoolboy_idle");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());

		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::WALK:
	{
		_enemyImg = IMAGE_MANAGER->findImage("schoolboy_walk");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::RUN:
	{
		_enemyImg = IMAGE_MANAGER->findImage("schoolboy_run");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::JUMP:
	{
		_enemyImg = IMAGE_MANAGER->findImage("schoolboy_jump");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(2);
		_ani->start();
	}
	break;
	case ENEMY_STATE::ATTACK:
	{
		int i = RANDOM->getFromIntTo(1, 4);
		if (i == 3)
		{
			_attackS = 3;
		}
		else
		{
			_attackS = 2;
		}
		char imgNameNum[128];
		sprintf_s(imgNameNum, "schoolboy_attack%d", i);
		_enemyImg = IMAGE_MANAGER->findImage(imgNameNum);
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::DASHATTACK:
	{
		_attackS = 2;
		_enemyImg = IMAGE_MANAGER->findImage("schoolboy_runAttack");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::JUMPATTACK:
	{
		_attackS = 2;
		_enemyImg = IMAGE_MANAGER->findImage("schoolboy_jumpAttack");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::GUARD:
	{
		_enemyImg = IMAGE_MANAGER->findImage("schoolboy_block");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(1);
		_ani->start();
	}
	break;
	case ENEMY_STATE::HIT:
	{
		_enemyImg = IMAGE_MANAGER->findImage("schoolboy_getHit");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(7);
		_ani->start();
	}
	break;
	case ENEMY_STATE::STUN:
	{
		_enemyImg = IMAGE_MANAGER->findImage("schoolboy_stun");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(7);
		_ani->start();
	}
	break;
	case ENEMY_STATE::KNOCKDOWN:
	{
		_enemyImg = IMAGE_MANAGER->findImage("schoolboy_knockDown");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		//if(direction == DIRECTION::RIGHT) _ani->setPlayFrame(0, 24, false, false);
		//else _ani->setPlayFrame(_enemyImg->getMaxFrameX(), 57, false, false);
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::STANDUP:
	{
		_enemyImg = IMAGE_MANAGER->findImage("schoolboy_standUp");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		//if (direction == DIRECTION::RIGHT) _ani->setPlayFrame(25, _enemyImg->getMaxFrameX(), false, false);
		//else _ani->setPlayFrame(58, _enemyImg->getMaxFrameX() * 2 - 1);
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::SKILL:
	{
		_attackS = 5;
		_enemyImg = IMAGE_MANAGER->findImage("schoolboy_skill");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::HELD:
	{
		_enemyImg = IMAGE_MANAGER->findImage("schoolboy_heldHit");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	}
}

void SchoolBoy::setDirectionToPlayer()
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
