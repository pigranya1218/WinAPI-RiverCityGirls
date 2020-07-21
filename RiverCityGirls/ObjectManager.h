#pragma once
#include "GameObject.h"

class Object;

class ObjectManager :
	public GameObject
{
private:
	Object* deskOb;
	Object* shcoolBoy01;
public:
	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();
};

