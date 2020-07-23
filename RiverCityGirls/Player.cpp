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
	setPosition(Vector3(500, -105, 500));
	setSize(Vector3(80, 210, 30));

	_state = new IdleState;
	_state->enter(*this);

	_direction = DIRECTION::RIGHT;
	
	_jumpPower = 12;
	_speed = 5;
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
	FloatRect rc = FloatRect(Vector2(_position.x, _position.z), Vector2(_size.x, _size.z), Pivot::Center);
	CAMERA_MANAGER->drawLine(Vector2(_position.x, _position.z), Vector2(_position.x, _position.z + _position.y));
	CAMERA_MANAGER->rectangle(rc, D2D1::ColorF::Enum::Red, 1, 1);
}

void Player::attack(FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	_stageManager->playerAttack(this, attackRc, damage, type);
}
