#pragma once
#include "Enemy.h"

class SchoolGirl : public Enemy
{
private:

public:
	SchoolGirl() {};
	~SchoolGirl() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

