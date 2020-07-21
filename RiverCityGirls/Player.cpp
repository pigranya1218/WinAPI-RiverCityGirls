#include "stdafx.h"
#include "Player.h"
#include "PlayerState.h"



Player::Player()
{
}

Player::~Player()
{
}

void Player::init()
{

}

void Player::release()
{
}

void Player::update()
{
	PlayerState* _newState = _state->update(*this);
	if (_newState != nullptr)
	{
		delete _state;
		_state = _newState;

	}
}

void Player::render()
{
}
