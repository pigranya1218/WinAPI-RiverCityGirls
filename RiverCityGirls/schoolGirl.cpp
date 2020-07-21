#include "stdafx.h"
#include "SchoolGirl.h"

HRESULT SchoolGirl::init()
{
	_enemyImg = IMAGE_MANAGER->findImage("½ºÄð°É_±âº»");

	_getHitRc = rectMakePivot(Vector2(WINSIZEX / 2 - 200, WINSIZEY / 2), Vector2(_enemyImg->getFrameSize())* 1.5f, Pivot::Center);

	_direction = IDLE;

	_ani = new Animation;
	_enemyImg = IMAGE_MANAGER->findImage("½ºÄð°É_±âº»");
	_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
		_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
	_ani->setPlayFrame(0, 8, false, true);
	_ani->setFPS(10);
	_ani->start();

	_x = (_getHitRc.left + _getHitRc.right) / 2;

	return S_OK;
}

void SchoolGirl::release()
{
}

void SchoolGirl::update()
{
	switch (_direction)
	{
	case IDLE:

	break;
	case WALK:

	break;
	case RUN:

	break;
	case JUMP:

	break;
	case ATTACK:

	break;
	case GUARD:

	break;
	case HIT:

	break;
	case DOWN:

	break;
	case STUN:

	break;
	case SKILL:

	break;
	case HELD:

	break;	
	}

}

void SchoolGirl::render()
{
}
