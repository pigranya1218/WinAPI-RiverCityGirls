#include "stdafx.h"
#include "schoolBoy.h"

HRESULT schoolBoy::init()
{
	_enemyImg = ImageManager::GetInstance()->FindImage("스쿨보이_기본");
	
	_getHitRc = RectMakePivot(Vector2(WINSIZEX/2 - 200, WINSIZEY/2), Vector2(_enemyImg->GetFrameSize())* 1.5f, Pivot::Center);

	_direction = IDLE;

	_ani = new Animation;
	_enemyImg = ImageManager::GetInstance()->FindImage("스쿨보이_기본");
	_ani->init(_enemyImg->GetWidth(), _enemyImg->GetHeight(),
		_enemyImg->GetMaxFrameX(), _enemyImg->GetMaxFrameY());
	_ani->setPlayFrame(0, 8, false, true);
	_ani->setFPS(10);
	_ani->start();

	_count = 0;
	return S_OK;
}

void schoolBoy::release()
{
}

void schoolBoy::update()
{
	//디렉션 테스트
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		aniPlay(WALK, 0);
	}
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		aniPlay(RUN, 0);
	}
	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		aniPlay(JUMP, 0);
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		aniPlay(ATTACK, 0);
	}
	if (KEYMANAGER->isOnceKeyDown('G'))
	{
		aniPlay(GUARD, 1);
	}

	//상태 패턴에 따른 디렉션 조정
	/*
	switch (_direction)
	{
	case IDLE:
		if ((_getHitRc.GetCenter > _ptMouse.x + 600 && _getHitRc.GetCenter().GetIntX > _ptMouse.x + 5) ||
			(_getHitRc.GetCenter().GetIntX < _ptMouse.x - 600 && _getHitRc.GetCenter().GetIntX < _ptMouse.x - 5))
		{
			_direction = RUN;
		}

		if (_getHitRc.GetCenter().GetIntX < _ptMouse.x + 500 && _getHitRc.GetCenter().GetIntX > _ptMouse.x + 5)
		{
			_direction = WALK;
		}
		else if (_getHitRc.GetCenter().GetIntX > _ptMouse.x - 500 && _getHitRc.GetCenter().GetIntX < _ptMouse.x - 5)
		{
			_direction = WALK;
		}

		break;
	case WALK:

		if (_getHitRc.GetCenter().GetIntX < _ptMouse.x + 500 && _getHitRc.GetCenter().GetIntX > _ptMouse.x + 5)
		{
			_getHitRc.left -= 2;
			_getHitRc.right -= 2;
		}
		else if (_getHitRc.GetCenter().GetIntX > _ptMouse.x - 500 && _getHitRc.GetCenter().GetIntX < _ptMouse.x - 5)
		{
			_getHitRc.left += 2;
			_getHitRc.right += 2;
		}
		if ((_getHitRc.GetCenter().GetIntX < _ptMouse.x + 70 && _getHitRc.GetCenter().GetIntX > _ptMouse.x + 5) || 
			(_getHitRc.GetCenter().GetIntX > _ptMouse.x - 70 && _getHitRc.GetCenter().GetIntX < _ptMouse.x - 5))
		{
			_direction = ATTACK;
		}
		else
		{
			_direction = WALK;
		}

		if (_getHitRc.GetCenter().GetIntX > _ptMouse.x + 600 || _getHitRc.GetCenter().GetIntX < _ptMouse.x - 600)
		{
			_direction = RUN;
		}


		break;
	case RUN:
		if (_getHitRc.GetCenter().GetIntX > _ptMouse.x && _getHitRc.GetCenter().GetIntX > _ptMouse.x + 5)
		{
			_getHitRc.left -= 5;
			_getHitRc.right -= 5;
		}
		else if (_getHitRc.GetCenter().GetIntX < _ptMouse.x && _getHitRc.GetCenter().GetIntX < _ptMouse.x - 5)
		{
			_getHitRc.left += 5;
			_getHitRc.right += 5;
		}

		if ((_getHitRc.GetCenter().GetIntX < _ptMouse.x + 70 && _getHitRc.GetCenter().GetIntX > _ptMouse.x + 5) ||
			(_getHitRc.GetCenter().GetIntX > _ptMouse.x - 70 && _getHitRc.GetCenter().GetIntX < _ptMouse.x - 5))
		{
			_direction = ATTACK;
		}


		break;
	case JUMP:



		break;
	case ATTACK:
		_count++;

		if (_count > 30)
		{
			_count = 0;
			_direction = WALK;
		}
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
	}*/

	_ani->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void schoolBoy::render()
{
	_enemyImg->SetScale(1.5f);
	//_enemyImg->FrameRender(Vector2(WINSIZEX / 2, WINSIZEY / 2), 0, 0);
	_enemyImg->AniRender(Vector2(WINSIZEX / 2 - 200, WINSIZEY / 2), _ani);
	D2DRenderer::GetInstance()->drawRectangle
	(
		_getHitRc,
		D2DRenderer::DefaultBrush::Red,
		1.f
	);
	//test
	char str[255];
	sprintf_s(str, "GetMaxFrameX = %d", _enemyImg->GetMaxFrameX());
	TextOut(_hdc, 0, 0, str, strlen(str));
}

void schoolBoy::aniPlay(DIRECTION direction, int numLR)
{
	//디렉션에 따른 애니메이션
	if (direction == WALK)
	{
		_ani = new Animation;
		_enemyImg = ImageManager::GetInstance()->FindImage("스쿨보이_걷기");
		_ani->init(_enemyImg->GetWidth(), _enemyImg->GetHeight(),
			_enemyImg->GetMaxFrameX(), _enemyImg->GetMaxFrameY());
		//좌측 0, 우측 1
		if (numLR == 0) _ani->setPlayFrame(_enemyImg->GetMaxFrameX(), _enemyImg->GetMaxFrameX()*2-1, false, true);
		if (numLR == 1) _ani->setPlayFrame(0, _enemyImg->GetMaxFrameX()-1, false, true);
		_ani->setFPS(10);
		_ani->start();
	}
	if (direction == RUN)
	{
		_ani = new Animation;
		_enemyImg = ImageManager::GetInstance()->FindImage("스쿨보이_달리기");
		_ani->init(_enemyImg->GetWidth(), _enemyImg->GetHeight(),
			_enemyImg->GetMaxFrameX(), _enemyImg->GetMaxFrameY());
		//좌측 0, 우측 1
		if (numLR == 0) _ani->setPlayFrame(_enemyImg->GetMaxFrameX(), _enemyImg->GetMaxFrameX() * 2 - 1, false, true);
		if (numLR == 1) _ani->setPlayFrame(0, _enemyImg->GetMaxFrameX() - 1, false, true);
		_ani->setFPS(10);
		_ani->start();
	}
	if (direction == JUMP)
	{
		_ani = new Animation;
		_enemyImg = ImageManager::GetInstance()->FindImage("스쿨보이_점프");
		_ani->init(_enemyImg->GetWidth(), _enemyImg->GetHeight(),
			_enemyImg->GetMaxFrameX(), _enemyImg->GetMaxFrameY());
		//좌측 0, 우측 1
		if (numLR == 0) _ani->setPlayFrame(_enemyImg->GetMaxFrameX(), _enemyImg->GetMaxFrameX() * 2 - 1, false, true);
		if (numLR == 1) _ani->setPlayFrame(0, _enemyImg->GetMaxFrameX() - 1, false, true);
		_ani->setFPS(10);
		_ani->start();
	}
	if (direction == ATTACK)
	{
		_ani = new Animation;
		int i = RND->getFromIntTo(1, 4);
		char imgNameNum[128]; 
		sprintf_s(imgNameNum, "스쿨보이_공격%d", i);
		_enemyImg = ImageManager::GetInstance()->FindImage(imgNameNum);
		_ani->init(_enemyImg->GetWidth(), _enemyImg->GetHeight(),
			_enemyImg->GetMaxFrameX(), _enemyImg->GetMaxFrameY());
		//좌측 0, 우측 1
		if (numLR == 0) _ani->setPlayFrame(_enemyImg->GetMaxFrameX(), _enemyImg->GetMaxFrameX() * 2 - 1, false, true);
		if (numLR == 1) _ani->setPlayFrame(0, _enemyImg->GetMaxFrameX() - 1, false, true);
		_ani->setFPS(10);
		_ani->start();
	}
	if (direction == GUARD)
	{
		_ani = new Animation;
		_enemyImg = ImageManager::GetInstance()->FindImage("스쿨보이_가드");
		_ani->init(_enemyImg->GetWidth(), _enemyImg->GetHeight(),
			_enemyImg->GetMaxFrameX(), _enemyImg->GetMaxFrameY());
		//좌측 0, 우측 1
		if (numLR == 0) _ani->setPlayFrame(_enemyImg->GetMaxFrameX(), _enemyImg->GetMaxFrameX() * 2 - 1, false, true);
		if (numLR == 1) _ani->setPlayFrame(0, _enemyImg->GetMaxFrameX() - 1, false, true);
		_ani->setFPS(10);
		_ani->start();
	}
	if (direction == HIT)
	{
		_ani = new Animation;
		_enemyImg = ImageManager::GetInstance()->FindImage("스쿨보이_피격");
		_ani->init(_enemyImg->GetWidth(), _enemyImg->GetHeight(),
			_enemyImg->GetMaxFrameX(), _enemyImg->GetMaxFrameY());
		//좌측 0, 우측 1
		if (numLR == 0) _ani->setPlayFrame(_enemyImg->GetMaxFrameX(), _enemyImg->GetMaxFrameX() * 2 - 1, false, true);
		if (numLR == 1) _ani->setPlayFrame(0, _enemyImg->GetMaxFrameX() - 1, false, true);
		_ani->setFPS(10);
		_ani->start();
	}
}
