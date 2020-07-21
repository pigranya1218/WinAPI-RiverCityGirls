#include "stdafx.h"
#include "PlayerState.h"


void PlayerState::enter(Player & player)
{
}

void PlayerState::exit(Player & player)
{
}

PlayerState * PlayerState::update(Player & player)
{
	return nullptr;
}

void PlayerState::render(Player & player)
{
}



//JumpState::JumpState()
//{
//	_jumpPower = 10;
//	_gravity = 0.3f;
//	_newImg = IMAGE_MANAGER->findImage("ÄìÄÚÁ¡ÇÁ");
//	_newAni = new Animation;
//	_newAni->init(_newImg->getWidth(), _newImg->getHeight(), _newImg->getMaxFrameX(), _newImg->getMaxFrameY());
//	_newAni->setDefPlayFrame(false, true);
//	_newAni->setFPS(2);
//	_newAni->start();
//}
//
//KyokoState * JumpState::update(Kyoko & Kyoko)
//{
//	Kyoko.setY(Kyoko.getY() - _jumpPower);
//	_jumpPower -= _gravity;
//	if (Kyoko.getDirection() == RIGHT)
//	{
//		if (_jumpPower > 2)
//		{
//			_newAni->setPlayFrame(0, 1, false, false);
//		}
//		if (_jumpPower < -1)
//		{
//			_newAni->setPlayFrame(2, 1, false, false);
//		}
//		if (_jumpPower >= -1 && _jumpPower <= 2)
//		{
//			_newAni->setPlayFrame(1, 2, false, false);
//		}
//	}
//	if (Kyoko.getDirection() == LEFT)
//	{
//		if (_jumpPower > 2)
//		{
//			_newAni->setPlayFrame(3, 4, false, false);
//		}
//		if (_jumpPower < -1)
//		{
//			_newAni->setPlayFrame(5, 4, false, false);
//		}
//		if (_jumpPower >= -1 && _jumpPower <= 2)
//		{
//			_newAni->setPlayFrame(4, 5, false, false);
//		}
//	}
//
//	if (KEY_MANAGER->isStayKeyDown(VK_RIGHT))
//	{
//
//		Kyoko.setX(Kyoko.getX() + 5);
//	}
//	if (KEY_MANAGER->isStayKeyDown(VK_LEFT))
//	{
//
//		Kyoko.setX(Kyoko.getX() - 5);
//	}
//
//	if (Kyoko.getY() >= WINSIZEY / 2)
//	{
//		if (KEY_MANAGER->isStayKeyDown(VK_RIGHT) || KEY_MANAGER->isStayKeyDown(VK_LEFT)) return new WalkState;
//		else return new IdleState;
//	}
//
//	_newAni->frameUpdate(TIME_MANAGER->getElapsedTime() * 10);
//
//	return nullptr;
//}
//
//void JumpState::render(Kyoko & Kyoko)
//{
//	_newImg->aniRender(Vector2(Kyoko.getX(), Kyoko.getY()), _newAni);
//}
//
//
