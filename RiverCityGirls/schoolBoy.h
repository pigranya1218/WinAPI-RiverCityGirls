#pragma once
#include "enemy.h"

class schoolBoy : public enemy
{
private:
	int _count;

public:
	schoolBoy() {};
	~schoolBoy() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void aniPlay(DIRECTION direction, int numLR);
};

