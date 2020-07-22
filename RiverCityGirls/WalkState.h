#pragma once
#include "PlayerState.h"

class WalkState :public PlayerState
{
private:
	enum class WALK_STATE
	{
		MOVE,
		IDLE
	};

	float _initTime;
	WALK_STATE _state;

	Vector3 moveDir;

public:
	virtual PlayerState* update(Player& player);
	virtual void render(Player& player);
	virtual void enter(Player& player);
	virtual void exit(Player& player);
};