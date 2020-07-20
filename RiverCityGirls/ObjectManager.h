#pragma once
#include "GameNode.h"

class Object;

class ObjectManager :
	public GameNode
{
private:
	Object* deskOb;
	Object* shcoolBoy01;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

