#pragma once
#include "PlayerState.h"

enum class GET_HIT_STATE
{
	GET_HIT,//�¾Ƽ� �����Ǵ� ����
	KNOCK_OUT,//�¾Ƽ� �������� ����
	KNOCK_DOWN,//�¾Ƽ� ���� ����
	STAND_UP//DOWN���� �Ͼ�� ����
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

