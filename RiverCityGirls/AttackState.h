#pragma once
#include "AllPlayerState.h"

enum class ATTACK_SKILL
{
	QC1,
	QC2,
	QC3,
	RUN_QC,
	JUMP_QC,
	GRAB_QC,
	HC,
	RUN_HC,
	JUMP_HC
};

class AttackState : public PlayerState
{
private:
	

	Synthesize(ATTACK_SKILL,_skill,Skill)
	Synthesize(float, _currJumpPower,CurrJumpPower) //���� ������ �Ҷ� ���� ������ ���� �Ŀ��� �״�� �ΰ�ޱ� ����  
	Synthesize(float, _currMoveDirX, CurrMoveDirX)
		
	FloatRect _attackRc;
	FloatRect _viewRc;
	float _initTime;
	float _lastPlayerY;
	bool _isCombo;
	bool _isFirstAttackCheck;
	bool _isStep;

	int num2;
	int num3;
public:
	virtual void enter(Player&player);
	virtual PlayerState* update(Player& player);
	virtual void render(Player& player);
	virtual void exit(Player& paleyr);
};

