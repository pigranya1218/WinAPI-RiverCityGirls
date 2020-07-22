#pragma once
#include "PlayerState.h"

enum class JUMP_TYPE : int //
{
	RUN_JUMP,
	DEFAULT_JUMP
};

class JumpState : public PlayerState
{
private:
	float _gravity;
	Synthesize(JUMP_TYPE,_jumpType,JumpType)

public:


	virtual PlayerState* update(Player& player);
	virtual void render(Player& player);
	virtual void enter(Player& player);
	virtual void exit(Player& player);
};

