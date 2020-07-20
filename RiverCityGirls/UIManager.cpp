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

	_playerHp.playerBar = new ProgressBar;
	_playerHp.frameHp = IMAGE_MANAGER->findImage("playerHpFrame");
	_playerHp.playerBar->init("playerBackBar", "playerFrontBar", Vector2(WINSIZEX / 2 - 308, 43));

	_bossHp.bossBar = new ProgressBar;	
	_bossHp.frameHp	= IMAGE_MANAGER->findImage("bossHpFrame");
	_bossHp.bossBar->init("bossBackBar", "bossFrontBar", Vector2(WINSIZEX / 2 - 80, WINSIZEY - 90));	// 보스 체력 위치설정

	_cellPhone.phoneImg = IMAGE_MANAGER->findImage("startMapPhone");
	_cellPhone.x = WINSIZEX / 2 - 200;
	_cellPhone.y = WINSIZEY - 10;
	_cellPhone.height = 0;
	


	_playerHp.active = _bossHp.active = _cellPhone.active = _door.active = 0;
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
		_playerHp.playerBar->update();
		_playerHp.playerBar->setGauge(_playerHp.currentHp, _playerHp.maxHp);
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
		_playerHp.playerBar->render();
		_playerHp.frameHp->render(Vector2(WINSIZEX / 2 - 320, _playerHp.frameHp->getHeight() / 2 + 30));
		IMAGE_MANAGER->findImage("kyokoShot")->render(Vector2(WINSIZEX / 2 - 565, 80));
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
	if (_door.active)
	{
		_door.doorImg->setAlpha(_door.alpha);
		_door.doorImg->render(_door.pos);
	}
}

void UIManager::setDoorLock(bool active, const Vector2& pos, currentDoor currentDoor, float alpha)
{
	_door.active = active;
	_door.alpha = alpha;
	_door.pos = pos;
	
	switch (currentDoor)
	{
		case currentDoor::LOCK:		_door.doorImg = IMAGE_MANAGER->findImage("lockDoor");	break;
		case currentDoor::UNLOCK:	_door.doorImg = IMAGE_MANAGER->findImage("unlockDoor"); break;
	}
}
