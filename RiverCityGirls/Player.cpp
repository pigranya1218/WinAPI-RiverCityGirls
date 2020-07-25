#include "stdafx.h"
#include "Player.h"
#include "AllPlayerState.h"
#include "StageManager.h"


Player::Player()
{
}

Player::~Player()
{
}

void Player::move(Vector3 moveDir)
{
	_stageManager->moveGameObject(this, moveDir);
}

void Player::init()
{
	setPosition(Vector3(330, -105, 600));
	setSize(Vector3(80, 210, 30));

	_state = new IdleState;
	_state->enter(*this);

	_direction = DIRECTION::RIGHT;

	_team = OBJECT_TEAM::PLAYER;
	_jumpPower = 25;
	_gravity = 1.0f;
	_speed = 5;
	_maxHp = 100;
	_hp = _maxHp;
	_onObject = false;
	_damageTime = 0;
	_isHit = false;
	_mortalTime = 0;
}

void Player::release()
{
	_state->exit(*this);
	delete _state;

	//_attackState->exit(*this); 
	//delete _attackState;
}

void Player::update()
{
	

	PlayerState* _newState = _state->update(*this);
	if (_newState != nullptr)
	{
		_state->exit(*this);
		delete _state;
		_state = _newState;
		_damageTime = 0;
		_state->enter(*this);
	}

	

	/*AttackState* _newAttackState = _attackState->update(*this);
	if (_newAttackState != nullptr)
	{
		_attackState->exit(*this);
		delete _attackState;
		_attackState = _newAttackState;
		_attackState->enter(*this);
	}*/
}

void Player::render()
{
	_state->render(*this);

	if (DEBUG_MANAGER->isDebugMode(DEBUG_TYPE::PLAYER))
	{
		FloatRect rc = FloatRect(Vector2(_position.x, _position.z + _position.y + (_size.y / 2)), Vector2(_size.x, _size.z), Pivot::Center);
		CAMERA_MANAGER->drawLine(Vector2(_position.x, _position.z), Vector2(_position.x, _position.z + _position.y));
		CAMERA_MANAGER->rectangle(rc, D2D1::ColorF::Enum::Red, 1, 1);
	}
	
}

float Player::getCenterBottom()
{
	return _stageManager->getCenterBottom(_position);
}

void Player::attack(FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	_stageManager->playerAttack(this, attackRc, damage, type);
}

void Player::getHit(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	
	if (_isHit)return; 
		

	_getHitType = type;
	_damage = damage;


	Vector3 enemyPos = hitter->getPosition();
	Vector3 enemySize = hitter->getSize();
	float hitterMinZ = enemyPos.z - enemySize.z / 2;
	float hitterMaxZ = enemyPos.z + enemySize.z / 2;
	float playerMinZ = _position.z - _size.z / 2;
	float playerMaxZ = _position.z + _size.z / 2;

	if (playerMaxZ<hitterMinZ || playerMinZ>hitterMaxZ) return;

	FloatRect getHitRc = FloatRect(_position.x - _size.x / 2, _position.y - _size.y / 2, _position.x + _size.x / 2, _position.y + _size.y / 2);
	if (FloatRect::intersect(getHitRc, attackRc))
	{

		if (hitter->getPosition().x > _position.x)
		{
			_direction == DIRECTION::RIGHT;
		}
		else
		{
			_direction = DIRECTION::LEFT;
		}

		PlayerState* state = new getHitState;
		_state->exit(*this);
		delete _state;
		_state = state;
		state->enter(*this);
		return;
	}
}