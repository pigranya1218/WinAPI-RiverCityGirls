#pragma once
#include "GameObject.h"
class Obstacle : public GameObject
{
public:
	Obstacle();
	~Obstacle();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override; 

	void OnCollision(){}
};

