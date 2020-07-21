#pragma once
#include "GameNode.h"





class KyokoState;

class Kyoko : public GameNode
{
private:
	
	
	RECT _rc; //�ǰ�������Ʈ
	RECT _hitRc;//Ÿ��������Ʈ
	float _x, _y;//��Ʈ,�̹���, Ÿ�ݷ�Ʈ ����
	float _speed;//walk �ӵ�
	DIRECTION _direction;

	KyokoState* _state;

public:


	Kyoko();
	~Kyoko();

	HRESULT init();
	void release();
	void update();
	void render();

	//������� getter�� setter
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
