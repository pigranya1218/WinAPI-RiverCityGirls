#pragma once
#include "PlayerState.h"

class RunState : public PlayerState
{
public:
	virtual PlayerState* update(Player& player);
	virtual void render(Player& player);
	virtual void enter(Player& player);
	virtual void exit(Player& player);
};
