#pragma once
#include "PlayerState.h"

enum class GET_HIT_STATE
{
	GET_HIT,//맞아서 경직되는 상태
	KNOCK_OUT,//맞아서 쓰러지는 상태
	KNOCK_DOWN,//맞아서 누운 상태
	STAND_UP//DOWN에서 일어나는 상태
};

class getHitState : public PlayerState
{
private: 
	float _getHitTerm;

public:
	virtual void enter(Player& player);
	virtual void exit(Player& player);
	virtual PlayerState* update(Player& player);
	virtual void render(Player& player);
};

