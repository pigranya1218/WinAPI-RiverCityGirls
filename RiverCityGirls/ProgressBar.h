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

	// 뒤 이미지, 앞 이미지, 출력좌표
	HRESULT init(string backBarImage, string frontBarImage, const Vector2& pos);
	void release();
	void update();
	void render();
	
	void setGauge(float currentHp, float maxHp);


};

