#include "stdafx.h"
#include "UIManager.h"
#include "GameObject.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

HRESULT UIManager::init(Player* player)
{
	HRESULT result;

	_player = player;	

	ZeroMemory(&_playerInfo,	sizeof(_playerInfo));
	ZeroMemory(&_bossInfo,		sizeof(_bossInfo));
	ZeroMemory(&_close,			sizeof(_close));
	ZeroMemory(&_levelInfo,		sizeof(_levelInfo));
	ZeroMemory(&_cellPhone,		sizeof(_cellPhone));

	result = _playerInfo.init();
	result = _bossInfo.init();
	result = _levelInfo.init();
	result = _close.init();
	result = _shop.init();	

	/*_cellPhone.phoneImg = IMAGE_MANAGER->findImage("startMapPhone");
	_cellPhone.x = WINSIZEX / 2 - 200;
	_cellPhone.y = WINSIZEY - 10;
	_cellPhone.height = 0;*/
	
	
	return result;
}

void UIManager::release()
{
}

void UIManager::update()
{
	// 플레이어 컨트롤
	_playerInfo.update(_player);
	
	// 보스 체력
	_bossInfo.update();

	//레벨업!!	
	_levelInfo.update(_player->getPosition());

	if (!_vDoor.empty())
	{
		for (int i = 0; i < _vDoor.size(); i++)
		{			
			_vDoor[i].update(_player->getPosition());
		}
	}

	_close.update();

	_shop.update();

	_lock.update();

	// 플레이어 체력이 트루면 현재 플레이 중 && 핸드폰 보기
	/*if (KEY_MANAGER->isOnceKeyDown(VK_SPACE) && _playerHp.active)
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
	}*/
}

void UIManager::render()
{
	_lock.render();

	_playerInfo.render();
	_bossInfo.render();
	_levelInfo.render();

	if (!_vDoor.empty())
	{
		for (int i = 0; i < _vDoor.size(); i++)
		{
			_vDoor[i].render();
		}
	}		

	// _close.render(_player->getPosition());

	// _shop.render();
	
	/*if (_cellPhone.active)
	{
		_cellPhone.phoneImg->setSize(Vector2(_cellPhone.phoneImg->getWidth(), _cellPhone.height));
		_cellPhone.phoneImg->setScale(0.75f);
		_cellPhone.phoneImg->render(Vector2(_cellPhone.x, _cellPhone.y));
	}	*/
}

void UIManager::setLevelUp(bool active)
{
	_levelInfo.active = active;

	_levelInfo.pos = _player->getPosition();

	_levelInfo.playerAni->start();
}

void UIManager::setDoor(vector<tagDoorInfo> doors)
{
	_vDoor.clear();

	for (int i = 0; i < doors.size(); i++)
	{
		tagDoorInfo door;
		door.init(doors[i].doorState, doors[i].pos);

		_vDoor.push_back(door);
	}
}

void UIManager::setLock(LOCK_STATE state)
{	
	_lock.init(state);
}
