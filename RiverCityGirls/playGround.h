#pragma once
#include "gameNode.h"
#include "Kyoko.h"

class playGround : public gameNode
{
private: 
	Kyoko* _kyoko;
	

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

