#pragma once
#include "GameObject.h"
#include "animation.h"
#include "image.h"

class Player : public GameObject
{
private:
	Synthesize(Image*, mImg, Image)
	Synthesize(animation*, mAni, Animation)

public:
	Player();
	virtual ~Player();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

	void Move(Vector2 moveDirection, float speed);
	void MoveAngle(float angle,float speed);
};

