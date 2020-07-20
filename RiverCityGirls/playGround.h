#pragma once
#include "gameNode.h"
#include "enemyManager.h"

class playGround : public gameNode
{
private:
	enemyManager* _enemyMg;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

