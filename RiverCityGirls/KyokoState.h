#pragma once
#include "Kyoko.h"

class KyokoState
{
protected:
	Image* _newImg;
	//animation* _newAni;

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
	
	virtual void imageEnter(Kyoko& Kyoko);
	virtual KyokoState* update(Kyoko& Kyoko);
	virtual void render(Kyoko& Kyoko);
};

class RunningState : public KyokoState
{
public:
	
	virtual void imageEnter(Kyoko& Kyoko);
	virtual KyokoState* update(Kyoko& Kyoko);
	virtual void render(Kyoko& Kyoko);



};


