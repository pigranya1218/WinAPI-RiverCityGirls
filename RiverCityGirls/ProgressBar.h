#pragma once
#include "GameNode.h"

class ProgressBar : public GameNode
{
private:
	Image*	_frontBar;
	Image*	_backBar;
	Vector2 _pos;
	float	_width;	

public:
	ProgressBar();
	~ProgressBar();

	// �� �̹���, �� �̹���, �����ǥ
	HRESULT init(string backBarImage, string frontBarImage, const Vector2& pos);
	void release();
	void update();
	void render();
	
	void setGauge(float currentHp, float maxHp);


};

