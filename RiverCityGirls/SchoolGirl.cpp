#include "stdafx.h"
#include "SchoolGirl.h"

void SchoolGirl::init()
{
	_enemyImg = IMAGE_MANAGER->findImage("shoolgirl_idle");
	_position = Vector3(1000, -105, 500);
	_size = Vector3(80, 210, 30);
	_state = ENEMY_STATE::IDLE;
	_direction = DIRECTION::RIGHT;
	setState(_state, _direction);

	_gravity = 0;
	_jumpPower = 0;
	_hp = 100;
}

void SchoolGirl::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void SchoolGirl::update()
{

	_attackRc = FloatRect(0, 0, 0, 0);
	_viewRc = FloatRect(0, 0, 0, 0);
	
	
	Vector3 playerPos = _enemyManager->getPlayerPosition(); // �÷��̾��� ��ġ
	float distanceFromPlayer = sqrt(pow(playerPos.x - _position.x, 2) + pow(playerPos.z - _position.z, 2)); // �÷��̾�� xz �Ÿ�
	Vector3 moveDir = Vector3(0, 0, 0);
	_elapsedTime += TIME_MANAGER->getElapsedTime();

	// ���¿� ���� �ൿ �� ���� ����
	switch (_state)
	{
	case ENEMY_STATE::IDLE: // ��� ����
	{
		setDirectionToPlayer(); // �÷��̾� �ٶ󺸱�

		if (_elapsedTime > 1)
		{
			if (distanceFromPlayer > 400)
			{
				setState(ENEMY_STATE::RUN, _direction); // �÷��̾�� �޷�����
			}
			else
			{
				setState(ENEMY_STATE::WALK, _direction); // �÷��̾�� �ɾ��
			}
		}
	}
	break;

	case ENEMY_STATE::WALK: // �ȱ� ����
	{
		setDirectionToPlayer(); // �÷��̾� �ٶ󺸱�

		_gravity += 1;

		moveDir.x += (_direction == DIRECTION::RIGHT) ? 1 : -1;
		moveDir.z += (playerPos.z >= _position.z + 10) ? 1 : ((playerPos.z <= _position.z - 10) ? -1 : 0);
		moveDir = Vector3::normalize(&moveDir);
		moveDir = moveDir * 2;
		moveDir.y += _gravity;

		float lastY = _position.y;
		_enemyManager->moveEnemy(this, moveDir);
		float currY = _position.y;

		if (lastY != currY) // ������
		{
			setState(ENEMY_STATE::JUMP, _direction);
		}
		else
		{
			_gravity = 0;
			if (distanceFromPlayer <= 100) // ���� �� ����
			{
				setState(ENEMY_STATE::ATTACK, _direction);
			}
			else if (_elapsedTime >= 5) // ���� �������� ���� �ѹ� �����غ���
			{
				setState(ENEMY_STATE::JUMP, _direction);
				_gravity = -22;
			}			
		}
		if (_elapsedTime > 2 && _position.x == _position.x  && playerPos.z >= _position.z)
		{
			_position.z += 1;
		}
		else
		{
			_position.z -= 1;
		}

		
	}
	break;
	case ENEMY_STATE::RUN:
	{
		setDirectionToPlayer(); // �÷��̾� �ٶ󺸱�

		_gravity += 1;

		moveDir.x += (_direction == DIRECTION::RIGHT) ? 1 : -1;
		moveDir.z += (playerPos.z >= _position.z + 10) ? 1 : ((playerPos.z <= _position.z - 10) ? -1 : 0);
		moveDir = Vector3::normalize(&moveDir);
		moveDir = moveDir * 4;
		moveDir.y += _gravity;

		float lastY = _position.y;
		_enemyManager->moveEnemy(this, moveDir);
		float currY = _position.y;

		if (lastY != currY) // ������
		{
			setState(ENEMY_STATE::JUMP, _direction);
		}
		else
		{
			_gravity = 0;
			if (distanceFromPlayer <= 100) // ���� �� ����
			{
				setState(ENEMY_STATE::DASHATTACK, _direction);
			}
			else if (_elapsedTime >= 5) // ���� �������� ���� �ѹ� �����غ���
			{
				setState(ENEMY_STATE::JUMP, _direction);
				_gravity = -26;
			}
		}
		if (_elapsedTime > 2 && _position.x == _position.x  && playerPos.z >= _position.z)
		{
			_position.z += 1;
		}
		else
		{
			_position.z -= 1;
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

		if (_gravity > 1 && lastY == currY) // ������ ���
		{
			_gravity = 0;
			if (distanceFromPlayer > 400)
			{
				setState(ENEMY_STATE::RUN, _direction); // �÷��̾�� �޷�����
			}
			else
			{
				setState(ENEMY_STATE::WALK, _direction); // �÷��̾�� �ɾ��
			}
		}
	}
	break;

	case ENEMY_STATE::ATTACK:
	{
		
		if (_direction == DIRECTION::LEFT)
		{
			_attackRc = FloatRect(_position.x - 130, _position.y - 35,
				_position.x - 20, _position.y + 20);
		}
		else if(_direction == DIRECTION::RIGHT)
		{
			_attackRc = FloatRect(_position.x + 20, _position.y - 35,
				_position.x + 100, _position.y + 20);
		}
		_viewRc = FloatRect(_attackRc.left, _position.z + _attackRc.top,
			_attackRc.right, _position.z + _attackRc.bottom);	

		//enemyAttack(_attackRc, 5, ATTACK_TYPE::HIT1); Ȱ��ȭ�Ǹ� ����

		

		if (!_ani->isPlay()) // ���� ����� �����ٸ�
		{
			setState(ENEMY_STATE::IDLE, _direction);
		}
		
		
	
	}
	break;

	case ENEMY_STATE::DASHATTACK:
	{
		
		if (_direction == DIRECTION::LEFT)
		{
			_attackRc = FloatRect(_position.x - 130, _position.y - 35,
				_position.x - 20, _position.y + 20);
		}
		else if (_direction == DIRECTION::RIGHT)
		{
			_attackRc = FloatRect(_position.x + 20, _position.y - 35,
				_position.x + 100, _position.y + 20);
		}
		_viewRc = FloatRect(_attackRc.left, _position.z + _attackRc.top,
			_attackRc.right, _position.z + _attackRc.bottom);
		if (!_ani->isPlay()) // ���� ����� �����ٸ�
		{
			setState(ENEMY_STATE::IDLE, _direction);
		}
	}
	break;

	case ENEMY_STATE::HIT: // ���� ����
	{
		_gravity += 1;
		moveDir.x += (_direction == DIRECTION::RIGHT) ? -1 : 1;
		moveDir.y += _gravity;

		float lastY = _position.y;
		_enemyManager->moveEnemy(this, moveDir);
		float currY = _position.y;

		if (lastY != currY) // ������
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

	case ENEMY_STATE::KNOCKDOWN: // �������� ����
	{
		_gravity += 1;
		moveDir.x += (_direction == DIRECTION::RIGHT) ? -1 : 1;
		moveDir.y += _gravity;

		float lastY = _position.y;
		_enemyManager->moveEnemy(this, moveDir);
		float currY = _position.y;

		if (lastY != currY) // ������
		{
		}
		else // �������� ����
		{
			_gravity = 0;
			if (_elapsedTime > 1.5f)
			{
				setState(ENEMY_STATE::STANDUP, _direction);
			}
		}
	}
	break;

	case ENEMY_STATE::STANDUP: // �������� �Ͼ�� ����
	{
		if (!_ani->isPlay())
		{
			setState(ENEMY_STATE::IDLE, _direction);
		}
	}
	break;

	case ENEMY_STATE::STUN: // ���� �ɸ� ����
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

void SchoolGirl::render()
{
	//�¿쿡 ���� �ִϸ��̼� ������ �� ���� ����
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
		CAMERA_MANAGER->rectangle(_viewRc, D2D1::ColorF::Enum::Red, 1, 1);
	}	


	_enemyImg->setScale(3);
	CAMERA_MANAGER->aniRenderZ(_enemyImg, _position, _size, _ani);
}


void SchoolGirl::hitEffect(GameObject * hitter, FloatRect attackRc, float damage, ATTACK_TYPE type)
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

void SchoolGirl::setState(ENEMY_STATE state, DIRECTION direction)
{
	_state = state;
	_elapsedTime = 0;

	//���¿� ���� �ִϸ��̼�
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
		sprintf_s(imgNameNum, "schoolgirl_attack%d", i);
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
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_attack3");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::JUMPATTACK:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_jumpAttack2");
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
		_ani->setFPS(8);
		_ani->start();
	}
	break;
	case ENEMY_STATE::STUN:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_stun");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(7);
		_ani->start();
	}
	break;
	case ENEMY_STATE::KNOCKDOWN:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_knockDown");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(15);
		_ani->start();
	}
	break;
	case ENEMY_STATE::STANDUP:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_standUp");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(8);
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
	}
}

void SchoolGirl::setDirectionToPlayer()
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



