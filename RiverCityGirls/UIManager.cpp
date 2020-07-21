#include "stdafx.h"
#include "UIManager.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

HRESULT UIManager::init()
{
	ZeroMemory(&_playerHp, sizeof(_playerHp));
	ZeroMemory(&_bossHp, sizeof(_bossHp));
	ZeroMemory(&_cellPhone, sizeof(_cellPhone));

	for (int i = 0; i < DOORMAX; i++)
	{
		ZeroMemory(&_door[i], sizeof(_door[i]));
	}

	_playerHp.frameHp = IMAGE_MANAGER->findImage("playerHpFrame");
	_playerHp.hpDigit = IMAGE_MANAGER->findImage("playerDigit");
	_playerHp.digitNum = PLAYERHPMAX;

	_bossHp.bossBar = new ProgressBar;	
	_bossHp.frameHp	= IMAGE_MANAGER->findImage("bossHpFrame");
	_bossHp.bossBar->init("bossBackBar", "bossFrontBar", Vector2(WINSIZEX / 2 - 70, WINSIZEY - 95), Vector2(-25.0f, 0.0f));	// 보스 체력 위치설정

	_cellPhone.phoneImg = IMAGE_MANAGER->findImage("startMapPhone");
	_cellPhone.x = WINSIZEX / 2 - 200;
	_cellPhone.y = WINSIZEY - 10;
	_cellPhone.height = 0;
	
	
	return S_OK;
}

void UIManager::release()
{
}

void UIManager::update()
{
	// 플레이어 체력
	if (_playerHp.active)
	{
		_playerHp.digitNum = (int)((_playerHp.currentHp / _playerHp.maxHp) * PLAYERHPMAX);	// 체력바 갯수 설정
		// 체력바는 0개인데 체력은 아직 남아있는 경우
		if (!_playerHp.digitNum && _playerHp.currentHp)
		{
			_playerHp.digitNum = 1;	// 체력바는 1로 만들어줌
		}
	}
	// 보스 체력
	if (_bossHp.active)
	{
		_bossHp.bossBar->update();
		_bossHp.bossBar->setGauge(_bossHp.currentHp, _bossHp.maxHp);
	}
	// 플레이어 체력이 트루면 현재 플레이 중 && 핸드폰 보기
	if (KEY_MANAGER->isOnceKeyDown(VK_SPACE) && _playerHp.active)
	{
		switch (_cellPhone.active)
		{
			case 0:
			{
				_cellPhone.active = true;
				_cellPhone.height = 0;
				break;
			}
			case 1:
			{
				_cellPhone.active = false;
				break;
			}
		}
	}
	if (_cellPhone.active)
	{
		if (_cellPhone.height < _cellPhone.phoneImg->getHeight())
		{
			_cellPhone.height += 15;
			_cellPhone.y -= 3;
		}
	}
}

void UIManager::render()
{
	IMAGE_MANAGER->findImage("screenBorder")->setSize(Vector2(WINSIZEX, WINSIZEY));
	IMAGE_MANAGER->findImage("screenBorder")->render(Vector2(WINSIZEX / 2, WINSIZEY / 2));	

	if (_playerHp.active)
	{	
		IMAGE_MANAGER->findImage("playerHPBackBar")->setAlpha(0.5f); // 흐음
		IMAGE_MANAGER->findImage("playerHPBackBar")->render(Vector2(WINSIZEX / 2 - 257, _playerHp.frameHp->getHeight() / 2 + 95));
		_playerHp.frameHp->render(Vector2(WINSIZEX / 2 - 320, _playerHp.frameHp->getHeight() / 2 + 100));
		for (int i = 0; i < _playerHp.digitNum; i++)
		{
			_playerHp.hpDigit->render(Vector2((float)(WINSIZEX / 2 - 435) + (i * (_playerHp.hpDigit->getWidth() / 2)), _playerHp.frameHp->getHeight() / 2 + 79));
		}
		
	}
	if (_bossHp.active)
	{
		_bossHp.bossBar->render();
		_bossHp.frameHp->render(Vector2(WINSIZEX / 2, WINSIZEY - 100));
	}
	if (_cellPhone.active)
	{
		_cellPhone.phoneImg->setSize(Vector2(_cellPhone.phoneImg->getWidth(), _cellPhone.height));
		_cellPhone.phoneImg->setScale(0.75f);
		_cellPhone.phoneImg->render(Vector2(_cellPhone.x, _cellPhone.y));
	}
	for (int i = 0; i < DOORMAX; i++)
	{
		if (_door[i].active)
		{
			_door[i].doorImg->setAlpha(_door[i].alpha);
			_door[i].doorImg->render(_door[i].pos);
		}
	}	
}

void UIManager::setDoorLock(int doorNum, bool active, const Vector2& pos, currentDoor currentDoor, float alpha)
{
	_door[doorNum].pos = pos;
	_door[doorNum].alpha = alpha;
	_door[doorNum].active = active;
	switch (currentDoor)
	{
		case currentDoor::LOCK:		_door[doorNum].doorImg = IMAGE_MANAGER->findImage("lockDoor");	break;
		case currentDoor::UNLOCK:	_door[doorNum].doorImg = IMAGE_MANAGER->findImage("unlockDoor");break;
		case currentDoor::SHOP:		_door[doorNum].doorImg = IMAGE_MANAGER->findImage("shop");		break;
	}
}
