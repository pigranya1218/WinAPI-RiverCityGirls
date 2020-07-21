#pragma once
#include "Player.h"

class PlayerState 
{
protected:
	Image* _img;
	Animation* _ani;

public:


	virtual PlayerState* update(Player& player);
	virtual void render(Player& player);

};


class IdleState : public PlayerState
{
private:
	int _dashCount;

public:
	IdleState();
	
	virtual PlayerState* update(Player& player);
	virtual void render(Player& player);
	virtual void enter(Player& player);
};

//�ȱ�
class WalkState :public PlayerState
{
private:
	int _dashCount;

public:
	WalkState();
	
	virtual PlayerState* update(Player& player);
	virtual void render(Player& player);
	virtual void enter(Player& player);
};

//�޸���
class RunningState : public PlayerState
{
public:
	RunningState();
	
	virtual PlayerState* update(Player& player);
	virtual void render(Player& player);
	virtual void enter(Player& player);
};


//
class JumpState :public PlayerState
{
private:


public:
	JumpState();

	virtual PlayerState* update(Player& player);
	virtual void render(Player& player);
	virtual void enter(Player& player);
};
