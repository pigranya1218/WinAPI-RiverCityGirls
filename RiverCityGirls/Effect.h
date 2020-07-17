#pragma once
#include "GameObject.h"

class Image;
class Animation;

class Effect : public GameObject
{
protected:
	Image*		_effectImage;
	Animation*	_effectAnimation;
	bool		_isRunning;
	float		_elapsedTime;

public:
	Effect();
	~Effect();

	virtual void init(Image* effectImage, int frameW, int frameH, int fps);
	virtual void release();
	virtual void update();
	virtual void render();

	void startEffect(int x, int y);
	void startEffect(int x, int y, int width, int height);

	virtual void killEffect();

	bool getIsRunning() { return _isRunning; }
};
