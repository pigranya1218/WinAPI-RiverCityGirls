#pragma once
#include "ProgressBar.h"

#define PLAYERHPMAX 29
#define DOORMAX 3

struct tagPlayerHp
{	
	Image* frameHp;
	Image* hpDigit;
	float currentHp;
	float maxHp;
	float x, y;
	bool active;
	int digitNum;
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
	LOCK, UNLOCK, SHOP
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

class UIManager
{
private:
	tagPlayerHp		_playerHp;
	tagBossHp		_bossHp;
	tagCellPhone	_cellPhone;
	tagDoor			_door[DOORMAX];

public:
	UIManager();
	~UIManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setDoorLock(int doorNum, bool active, const Vector2& pos, currentDoor currentDoor, float alpha = 1.0f);

	void setPlayerHpActive(bool active) { _playerHp.active = active; }
	void setPlayerHp(float currentHp, float maxHp) { _playerHp.currentHp = currentHp; _playerHp.maxHp = maxHp; }

	void setBossHpActive(bool active) { _bossHp.active = active; }
	void setBossHp(float currentHp, float maxHp) { _bossHp.currentHp = currentHp; _bossHp.maxHp = maxHp; }
};

