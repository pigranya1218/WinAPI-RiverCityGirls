#pragma once
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

class AttackState : public PlayerState
{
private:
	

	Synthesize(ATTACK_SKILL,_skill,Skill)
	Synthesize(float, _currJumpPower,CurrJumpPower) //���� ������ �Ҷ� ���� ������ ���� �Ŀ��� �״�� �ΰ�ޱ� ����  
	Synthesize(float, _currMoveDirX, CurrMoveDirX)
		
	FloatRect attackRc;
	FloatRect viewRc;
	float _initTime;
	float _lastPlayerY;

public:
	virtual void enter(Player&player);
	virtual PlayerState* update(Player& player);
	virtual void render(Player& player);
	virtual void exit(Player& paleyr);
};
