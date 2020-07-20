#include "stdafx.h"
#include "KyokoState.h"


void KyokoState::imageEnter(Kyoko & Kyoko)
{
}

//State ºÎ¸ðÅ¬·¡½º
KyokoState * KyokoState::update(Kyoko & Kyoko)
{
	return nullptr;
}

void KyokoState::render(Kyoko & Kyoko)
{
}




IdleState::IdleState()
{
	
	_newImg = IMAGE_MANAGER->findImage("ÄìÄÚ´ë±â");
	_newAni = new Animation;
	_newAni->init(_newImg->getWidth(), _newImg->getHeight(), _newImg->getMaxFrameX(), _newImg->getMaxFrameY());
	_newAni->setDefPlayFrame(false, true);
	_newAni->setFPS(2);
	_newAni->start();
}

void IdleState::imageEnter(Kyoko & Kyoko)
{
	
}

KyokoState * IdleState::update(Kyoko & Kyoko)
{
	

	if (Kyoko.getDirection() == RIGHT)
	{
		_newAni->setPlayFrame(0, 12, false, true);
	}
	if (Kyoko.getDirection() == LEFT)
	{
		_newAni->setPlayFrame(23, 12, false, true);
	}
	
	if (KEY_MANAGER->isOnceKeyDown('X'))
	{
		
		return new JumpState;
	}

	if (KEY_MANAGER->isOnceKeyDown(VK_RIGHT))
	{
		Kyoko.setDirection(RIGHT);		
		if(_newAni->getFramePos().x>6*_newImg->getMaxFrameX()) return new WalkState;
		else return new RunningState;
	}
	if (KEY_MANAGER->isOnceKeyDown(VK_LEFT))
	{
		Kyoko.setDirection(LEFT);
			
		if (_newAni->getFramePos().x > 6 * _newImg->getMaxFrameX()) return new WalkState;
		else return new RunningState;
	}
	

	_newAni->frameUpdate(TIME_MANAGER->getElapsedTime() * 10);

	return nullptr;
}

void IdleState::render(Kyoko & Kyoko)
{
	_newImg->aniRender(Vector2( Kyoko.getX(), Kyoko.getY()), _newAni);
}





WalkState::WalkState()
{
	_newImg = IMAGE_MANAGER->findImage("ÄìÄÚ°È±â");
	_newAni = new Animation;
	_newAni->init(_newImg->getWidth(), _newImg->getHeight(), _newImg->getMaxFrameX(), _newImg->getMaxFrameY());
	_newAni->setDefPlayFrame(false, true);
	_newAni->setFPS(2);
	_newAni->start();
}

void WalkState::imageEnter(Kyoko & Kyoko)
{
}

KyokoState * WalkState::update(Kyoko & Kyoko)
{
	if (Kyoko.getDirection() == RIGHT)
	{
		_newAni->setPlayFrame(0, 12, false, true);
		Kyoko.setX(Kyoko.getX() + 5);
	}
	if (Kyoko.getDirection() == LEFT)
	{
		_newAni->setPlayFrame(12, 24, false, true);
		Kyoko.setX(Kyoko.getX() - 5);
	}

	if (KEY_MANAGER->isOnceKeyUp(VK_RIGHT)|| KEY_MANAGER->isOnceKeyUp(VK_LEFT))
	{
		return new IdleState;
	}

	_newAni->frameUpdate(TIME_MANAGER->getElapsedTime() * 10);

	return nullptr;
}

void WalkState::render(Kyoko & Kyoko)
{
	_newImg->aniRender(Vector2(Kyoko.getX(), Kyoko.getY()), _newAni);
}





RunningState::RunningState()
{
	_newImg = IMAGE_MANAGER->findImage("ÄìÄÚ´Þ¸®±â");
	_newAni = new Animation;
	_newAni->init(_newImg->getWidth(), _newImg->getHeight(), _newImg->getMaxFrameX(), _newImg->getMaxFrameY());
	_newAni->setDefPlayFrame(false, true);
	_newAni->setFPS(2);
	_newAni->start();
}

void RunningState::imageEnter(Kyoko & Kyoko)
{
}

KyokoState * RunningState::update(Kyoko & Kyoko)
{
	if (Kyoko.getDirection() == RIGHT)
	{
		_newAni->setPlayFrame(0, 16, false, true);
		Kyoko.setX(Kyoko.getX() + 5);
	}
	if (Kyoko.getDirection() == LEFT)
	{
		_newAni->setPlayFrame(16, 32, false, true);
		Kyoko.setX(Kyoko.getX() - 5);
	}
	if (KEY_MANAGER->isOnceKeyUp(VK_RIGHT) || KEY_MANAGER->isOnceKeyUp(VK_LEFT))
	{
		return new IdleState;
	}

	_newAni->frameUpdate(TIME_MANAGER->getElapsedTime() * 10);

	return nullptr;
}

void RunningState::render(Kyoko & Kyoko)
{
	_newImg->aniRender(Vector2(Kyoko.getX(), Kyoko.getY()), _newAni);
}

JumpState::JumpState()
{
	_jumpPower = 10;
	_gravity = 0.3f;
	_newImg = IMAGE_MANAGER->findImage("ÄìÄÚÁ¡ÇÁ");
	_newAni = new Animation;
	_newAni->init(_newImg->getWidth(), _newImg->getHeight(), _newImg->getMaxFrameX(), _newImg->getMaxFrameY());
	_newAni->setDefPlayFrame(false, true);
	_newAni->setFPS(2);
	_newAni->start();
}

KyokoState * JumpState::update(Kyoko & Kyoko)
{
	Kyoko.setY(Kyoko.getY() - _jumpPower);
	_jumpPower -= _gravity;
	if (Kyoko.getDirection() == RIGHT)
	{
		if (_jumpPower > 2)
		{
			_newAni->setPlayFrame(0, 1, false, false);
		}
		if (_jumpPower < -1)
		{
			_newAni->setPlayFrame(2, 1, false, false);
		}
		if (_jumpPower >= -1 && _jumpPower <= 2)
		{
			_newAni->setPlayFrame(1, 2, false, false);
		}
	}
	if (Kyoko.getDirection() == LEFT)
	{
		if (_jumpPower > 2)
		{
			_newAni->setPlayFrame(3, 4, false, false);
		}
		if (_jumpPower < -1)
		{
			_newAni->setPlayFrame(5, 4, false, false);
		}
		if (_jumpPower >= -1 && _jumpPower <= 2)
		{
			_newAni->setPlayFrame(4, 5, false, false);
		}
	}

	if (Kyoko.getY() >= WINSIZEY / 2)
	{
		return new IdleState;
	}

	_newAni->frameUpdate(TIME_MANAGER->getElapsedTime() * 10);

	return nullptr;
}

void JumpState::render(Kyoko & Kyoko)
{
	_newImg->aniRender(Vector2(Kyoko.getX(), Kyoko.getY()), _newAni);
}
