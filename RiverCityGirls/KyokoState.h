#pragma once
#include "Kyoko.h"


class KyokoState
{
protected:
	Image* _newImg;
	Animation* _newAni;

	float _gravity;
	float _jumpPower;

public:
	
	virtual void imageEnter(Kyoko& Kyoko);
	virtual KyokoState* update(Kyoko& Kyoko);
	virtual void render(Kyoko& Kyoko);

};

//������
class IdleState : public KyokoState
{
private:
	int _dashCount;

public:
	IdleState();
	virtual void imageEnter(Kyoko& Kyoko);
	virtual KyokoState* update(Kyoko& Kyoko);
	virtual void render(Kyoko& Kyoko);
};

//�ȱ�
class WalkState:public KyokoState
{
private:
	int _dashCount;

public:
	WalkState();
	virtual void imageEnter(Kyoko& Kyoko);
	virtual KyokoState* update(Kyoko& Kyoko);
	virtual void render(Kyoko& Kyoko);
};

//�޸���
class RunningState : public KyokoState
{
public:
	RunningState();

	virtual void imageEnter(Kyoko& Kyoko);
	virtual KyokoState* update(Kyoko& Kyoko);
	virtual void render(Kyoko& Kyoko);

};


//
class JumpState:public KyokoState
{
private:
	

public:
	JumpState();

	virtual KyokoState* update(Kyoko& Kyoko);
	virtual void render(Kyoko& Kyoko);
};


