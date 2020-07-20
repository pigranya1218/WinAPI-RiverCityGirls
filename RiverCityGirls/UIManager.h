#pragma once
#include "singletonBase.h"
#include "ProgressBar.h"

struct tagPlayerHp
{	
	Image* frameHp;
	ProgressBar* playerBar;
	float currentHp;
	float maxHp;
	float x, y;
	bool active;
};

struct tagBossHp
{	
	Image* frameHp;
	ProgressBar* bossBar;
	float currentHp;
	float maxHp;
	float x, y;
	bool active;
};

enum class currentDoor
{
	LOCK, UNLOCK
};

struct tagDoor
{	
	Image*	doorImg;
	bool	active;
	Vector2	pos;
	float	alpha;
};

struct tagCellPhone
{
	Image* phoneImg;
	float x, y;
	bool active;
	float height;	
};

class UIManager : public SingletonBase<UIManager>
{
private:
	tagPlayerHp		_playerHp;
	tagBossHp		_bossHp;
	tagCellPhone	_cellPhone;
	tagDoor			_door;


public:
	UIManager();
	~UIManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setDoorLock(bool active, const Vector2& pos, currentDoor currentDoor, float alpha = 1.0f);

	void setPlayerHpActive(bool active) { _playerHp.active = active; }
	void setPlayerHp(float currentHp, float maxHp) { _playerHp.currentHp = currentHp; _playerHp.maxHp = maxHp; }

	void setBossHpActive(bool active) { _bossHp.active = active; }
	void setBossHp(float currentHp, float maxHp) { _bossHp.currentHp = currentHp; _bossHp.maxHp = maxHp; }
};

