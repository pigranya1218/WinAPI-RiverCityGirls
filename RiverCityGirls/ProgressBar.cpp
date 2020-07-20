#include "stdafx.h"
#include "ProgressBar.h"

ProgressBar::ProgressBar()
{
}

ProgressBar::~ProgressBar()
{
}

HRESULT ProgressBar::init(string backBarImage, string frontBarImage, const Vector2& pos)
{
	_backBar = IMAGE_MANAGER->findImage(backBarImage);
	_frontBar = IMAGE_MANAGER->findImage(frontBarImage);

	_pos = pos;

	_width = _backBar->getWidth();
	
	return S_OK;
}

void ProgressBar::release()
{

}

void ProgressBar::update()
{
}

void ProgressBar::render()
{
	_backBar->render(
		_pos, 
		Vector2(0, 0), 
		Vector2((float)_backBar->getWidth(), (float)_backBar->getHeight())
	);	
	_frontBar->render(
		_pos,											// ����� ��ġ
		Vector2(0, 0),									// �̹����� ������ġ
		Vector2(_width, (float)(_backBar->getHeight()))	// ������ ����, ����
	);
}

void ProgressBar::setGauge(float currentHp, float maxHp)
{
	_width = (currentHp / maxHp) * _backBar->getWidth();
}
