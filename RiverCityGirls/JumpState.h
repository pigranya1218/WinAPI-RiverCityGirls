#pragma once
#include "PlayerState.h"
class JumpState : public PlayerState
{
private:
	int _startY;
	float _jumpPower;
	float _gravity;

public:
	

	virtual PlayerState* update(Player& player);
	virtual void render(Player& player);
	virtual void enter(Player& player);

};

