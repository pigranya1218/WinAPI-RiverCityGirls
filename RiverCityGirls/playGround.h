#pragma once
#include "GameNode.h"
#include "Kyoko.h"

class playGround : public GameNode
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

