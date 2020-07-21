#pragma once
#include "GameNode.h"





class KyokoState;

class Kyoko : public GameNode
{
private:
	
	
	RECT _rc; //피격판정렉트
	RECT _hitRc;//타격판정렉트
	float _x, _y;//렉트,이미지, 타격렉트 중점
	float _speed;//walk 속도
	DIRECTION _direction;

	KyokoState* _state;

public:


	Kyoko();
	~Kyoko();

	HRESULT init();
	void release();
	void update();
	void render();

	//쿄고중점 getter와 setter
	float getX() { return _x; }
	float getY() { return _y; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

	DIRECTION getDirection() { return _direction; }
	void setDirection(DIRECTION direction) { _direction = direction; }
	void setImage(Image* image) { _img = image; }

	/*animation* getAnimation() { return _ani; }
	void setAnimation(animation* animation) {_ani= animation; }*/
};
