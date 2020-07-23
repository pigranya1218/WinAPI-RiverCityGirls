#pragma once
//#include "AttackState.h"
#include "AllPlayerState.h"

enum class ATTACK_SKILL
{
	QC1,
	QC2,
	QC3,
	RUN_QC,
	JUMP_QC,
	GRAB_QC
};

class WeakAttack : public PlayerState
{
private:
	

	Synthesize(ATTACK_SKILL,_skill,Skill)
	
	FloatRect attackRc;
	FloatRect viewRc;
	float _initTime;

public:
	virtual void enter(Player&player);
	virtual PlayerState* update(Player& player);
	virtual void render(Player& player);
	virtual void exit(Player& paleyr);
};

