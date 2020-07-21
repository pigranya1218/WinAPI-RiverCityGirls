#pragma once
#include "GameNode.h"

class ProgressBar : public GameNode
{
private:
	Image*	_frontBar;
	Image*	_backBar;
	Vector2 _pos;
	Vector2 _angle;
	float	_width;

public:
	ProgressBar();
	~ProgressBar();

	// 뒤 이미지, 앞 이미지, 출력좌표
	HRESULT init(string backBarImage, string frontBarImage, const Vector2& pos, const Vector2& angle = Vector2(0.0f, 0.0f));
	void release();
	void update();
	void render();
	
	void setGauge(float currentHp, float maxHp);


};

