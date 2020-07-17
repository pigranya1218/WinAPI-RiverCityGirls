#pragma once
#include "GameObject.h"
class Obstacle : public GameObject
{
public:
	Obstacle();
	~Obstacle();

	void init()override;
	void release()override;
	void update()override;
	void render()override; 

	void OnCollision(){}
};

