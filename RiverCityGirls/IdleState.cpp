#include "stdafx.h"
#include "KyokoState.h"




KyokoState * IdleState::update(Kyoko & Kyoko)
{

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		Kyoko.setDirection(RIGHT);
		return new WalkState;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		Kyoko.setDirection(LEFT);
		return new WalkState;
	}

	

	return nullptr;
}

void IdleState::render(Kyoko & Kyoko)
{
	
}


void IdleState::ImageEnter(Kyoko & Kyoko)
{
	Kyoko.setImage(_newImg = ImageManager::GetInstance()->FindImage("ÄìÄÚ´ë±â"));
	//animation* _newAni = new animation;
	//_newAni->init(_newImg->GetWidth(), _newImg->GetHeight(), _newImg->GetMaxFrameX(), _newImg->GetMaxFrameY());
	////_newAni->setDefPlayFrame(false, true);
	//_newAni->setFPS(2);
	//_newAni->setPlayFrame(0, 12, false, true);
}