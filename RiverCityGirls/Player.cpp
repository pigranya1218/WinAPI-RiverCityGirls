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
	_stageManager->moveGameObject(*this, moveDir);
}

void Player::init()
{
	setPosition(Vector3(500, 0, 500));
	setSize(Vector3(100, 100, 100));

	_state = new IdleState;
	_state->enter(*this);

	_speed = 5;
}

void Player::release()
{
	_state->exit(*this);
	delete _state;
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
}

void Player::render()
{
	_state->render(*this);
}
