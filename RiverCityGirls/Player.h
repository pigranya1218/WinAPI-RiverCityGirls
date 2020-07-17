#pragma once
#include "GameObject.h"
#include "animation.h"
#include "image.h"

class Player : public GameObject
{
private:
	Synthesize(Image*, _img, Image)
	Synthesize(Animation*, _ani, Animation)

public:
	Player();
	virtual ~Player();

	void init()override;
	void release()override;
	void update()override;
	void render()override;

	void move(Vector2 moveDirection, float speed);
	void moveAngle(float angle,float speed);
};

