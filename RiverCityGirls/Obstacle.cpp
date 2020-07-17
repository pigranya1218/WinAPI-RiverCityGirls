#include "stdafx.h"
#include "Obstacle.h"


Obstacle::Obstacle()
{
	_name = "Obstacle";
	_position = Vector2(WINSIZEX / 2, WINSIZEY / 2 - 100);
	_size = Vector2(300, 50);
	_rect = rectMakePivot(_position, _size, Pivot::Center);
	_active = true;
}
Obstacle::~Obstacle() {}

void Obstacle::init() {}

void Obstacle::release() {}

void Obstacle::update() {}

void Obstacle::render()
{
	D2DRenderer::GetInstance()->drawRectangle(_rect,
		D2DRenderer::DefaultBrush::Blue, 1.f);
}
