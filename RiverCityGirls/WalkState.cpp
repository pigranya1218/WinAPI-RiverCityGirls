#include "stdafx.h"
#include "KyokoState.h"



//°È±â



KyokoState * WalkState::update(Kyoko& Kyoko)
{
	ImageEnter(Kyoko);

	if (Kyoko.getDirection()==RIGHT)
	{
		Kyoko.setX(Kyoko.getX() + 5);
	}
	if (Kyoko.getDirection() == LEFT)
	{
		Kyoko.setX(Kyoko.getX() - 5);
	}
	if(KEYMANAGER->isOnceKeyUp(VK_RIGHT)||KEYMANAGER->isOnceKeyUp(VK_LEFT)) return new IdleState;
	

		/*if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			Kyoko.setDirection(RIGHT);
			return new RunningState;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			Kyoko.setDirection(LEFT);
			return new RunningState;
		}*/
	

	


	return nullptr;


}

void WalkState::render(Kyoko & Kyoko)
{
	
}


void WalkState::ImageEnter(Kyoko & Kyoko)
{
	Kyoko.setImage(ImageManager::GetInstance()->FindImage("ÄìÄÚ°È±â"));
	
	animation* _newAni = new animation;
	_newAni->init(_newImg->GetWidth(), _newImg->GetHeight(), _newImg->GetMaxFrameX(), _newImg->GetMaxFrameY());
	//_newAni->setDefPlayFrame(false, true);
	_newAni->setFPS(2);
	_newAni->setPlayFrame(0, 12, false, true);
}