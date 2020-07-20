#pragma once
#include "enemy.h"

class schoolGirl : public enemy
{
private:

public:
	schoolGirl() {};
	~schoolGirl() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

