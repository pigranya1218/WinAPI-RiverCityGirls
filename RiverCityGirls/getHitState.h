#pragma once
#include "PlayerState.h"

enum class GET_HIT_STATE
{
	HIT,//�¾Ƽ� �����Ǵ� ����
	HIT2,//�¾Ƽ� �����Ǵ� ����2
	KNOCK_DOWN,//�¾Ƽ� ���� ����
	STAND_UP,//DOWN���� �Ͼ�� ����
	STUN
};

class getHitState : public PlayerState
{
private: 
	float _getHitTerm;
	float lastPlayerY;
	float currentPlayerY;
	float _downTime;
	float _airBorne;

	ATTACK_TYPE _getHitType;
	Synthesize(GET_HIT_STATE, _getHitState,GetHitState)

	
	//int _hitAniArr[10];

public:
	virtual void enter(Player& player);
	virtual void exit(Player& player);
	virtual PlayerState* update(Player& player);
	virtual void render(Player& player);
	void setGetHitAni(Player& player);
	void setMotalTime(Player& player);
};

