#include "stdafx.h"
#include "Kyoko.h"
#include "KyokoState.h"

Kyoko::Kyoko()
{
}

Kyoko::~Kyoko()
{
}

HRESULT Kyoko::init()
{


	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	_speed = 2;
	_rc = RectMakeCenter(_x, _y, 50, 100);
	
	_state = new IdleState;

	_img = IMAGE_MANAGER->findImage("ÄìÄÚ´ë±â");
	_ani = new Animation;
	_ani->init(_img->getWidth(),_img->getHeight(),_img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(2);
	_ani->start();



	return S_OK;
}

void Kyoko::release()
{
}

void Kyoko::update()
{


	KyokoState* _newState= _state->update(*this);
	if (_newState != nullptr)
	{
		delete _state;
		_state = _newState;
		
	}

	_state->imageEnter(*this);
	
	_ani->frameUpdate(TIME_MANAGER->getElapsedTime() * 10);

	
	
	

}

void Kyoko::render()
{
	//_state->render(*this);

		//Image* image = ImageManager::GetInstance()->FindImage("ÄìÄÚ°È±â");
		//image->FrameRender(Vector2(_x, _y), 0, 0);
	//_img->SetSize(Vector2(140, 200));
	_img->aniRender(Vector2(_x, _y), _ani);
	
}

