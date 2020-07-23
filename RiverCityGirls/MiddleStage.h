#pragma once
#include "Stage.h"
class MiddleStage : public Stage
{
private:

public:
	virtual void init(Image* background, float bgScale);
	virtual void enter();
	virtual void exit();
	virtual Stage* update();
	virtual void render();
};
