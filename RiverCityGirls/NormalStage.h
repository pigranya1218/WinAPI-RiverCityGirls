#pragma once
#include "Stage.h"
class NormalStage : public Stage
{
private:

public:
	virtual void init(Image* background);
	virtual void enter();
	virtual void exit();
	virtual Stage* update();
	virtual void render();
};

