#pragma once
#include "Enemy.h"

class SchoolBoy : public Enemy
{
private:
	int _count;

public:
	SchoolBoy() {};
	~SchoolBoy() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void aniPlay(ENEMY_STATE direction, int numLR);
};

