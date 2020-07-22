#pragma once
#include "Player.h"

class AttackState
{
public:
	virtual void enter(Player&player);
	virtual AttackState* update(Player& player);
	virtual void render(Player& player);
	virtual void exit(Player& paleyr);

};

