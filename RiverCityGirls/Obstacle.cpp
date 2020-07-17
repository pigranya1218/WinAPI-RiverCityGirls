#include "stdafx.h"
#include "Obstacle.h"


Obstacle::Obstacle()
{
	mName = "Obstacle";
	mPosition = Vector2(WINSIZEX / 2, WINSIZEY / 2 - 100);
	mSize = Vector2(300, 50);
	mRect = RectMakePivot(mPosition, mSize, Pivot::Center);
	mActive = true;
}
Obstacle::~Obstacle() {}

void Obstacle::Init() {}

void Obstacle::Release() {}

void Obstacle::Update() {}

void Obstacle::Render()
{
	D2DRenderer::GetInstance()->drawRectangle(mRect,
		D2DRenderer::DefaultBrush::Blue, 1.f);
}
