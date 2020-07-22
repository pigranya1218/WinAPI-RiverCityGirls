#pragma once
#include "Player.h"

class AttackState
{
protected:
	Image* _img;
	Animation* _ani;
	RECT _hitRc;

public:
	virtual void enter(Player&player);
	virtual AttackState* update(Player& player);
	virtual void render(Player& player);
	virtual void exit(Player& player);

};

