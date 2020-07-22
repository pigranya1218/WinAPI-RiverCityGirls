#pragma once
//#include "AttackState.h"
#include "AllPlayerState.h"

class WeakAttack : public PlayerState
{
private:
	enum class ATTACK_COMBO
	{
		QC1,
		QC2,
		QC3
	};

	Synthesize(ATTACK_COMBO, _combo, Combo)
	 

public:
	virtual void enter(Player&player);
	//virtual AttackState* update(Player& player);
	virtual PlayerState* update(Player& player);
	virtual void render(Player& player);
	virtual void exit(Player& paleyr);
};

