#pragma once
#include "ProgressBar.h"

#define PLAYERHPMAX 23
#define DOORMAX 3

struct tagPlayerInfo
{	
	Image*	frameHp;	// ü�� ������
	Image*	hpDigit;	// ü�� ��ĭ �̹���
	float	currentHp;	// ���� ü��
	float	maxHp;		// �ִ� ü��	
	Vector2 pos;		// ��ǥ
	bool	active;		// ��� �� ������Ʈ ����
	int		digitNum;	// ü�� ĭ ����

	// ����ġ ����
	ProgressBar* expBar;		// ����ġ ����
	float		 currentExp;	// ���� ����ġ
	float		 maxExp;		// �ִ� ����ġ

	HRESULT init()
	{
		frameHp = IMAGE_MANAGER->findImage("playerHpFrame");
		hpDigit = IMAGE_MANAGER->findImage("playerDigit");
		digitNum = PLAYERHPMAX;
		expBar = new ProgressBar;
		expBar->init("playerExpBack", "playerExpFront", Vector2(WINSIZEX / 2 - 288.0f, 61.3f), Vector2(-30.0f, 0.0f), 0.7f);

		return S_OK;
	}
	void update()
	{
		if (active)
		{
			digitNum = (int)((currentHp / maxHp) * PLAYERHPMAX);	// ü�¹� ���� ����

			// ü�¹ٴ� 0���ε� ü���� ���� �����ִ� ���
			if (!digitNum && currentHp)
			{
				digitNum = 1;	// ü�¹ٴ� 1�� �������
			}
			expBar->update();
			expBar->setGauge(currentExp, maxExp);
		}
	}
	void render()
	{
		if (active)
		{
			IMAGE_MANAGER->findImage("playerBackBar")->setAlpha(0.8f);
			IMAGE_MANAGER->findImage("playerBackBar")->setScale(0.7f);
			IMAGE_MANAGER->findImage("playerBackBar")->render(Vector2(WINSIZEX / 2 - 275.0f, frameHp->getHeight() / 3.0f));

			expBar->render();
			frameHp->setScale(0.7f);
			frameHp->render(Vector2(WINSIZEX / 2 - 320.0f, frameHp->getHeight() / 2.8f));

			for (int i = 0; i < digitNum; i++)
			{
				hpDigit->setScale(0.7f);
				hpDigit->render(Vector2((float)(WINSIZEX / 2 - 400) + (i * (hpDigit->getWidth() / 2.25f)), frameHp->getHeight() / 3.8f));
			}
		}
	}
};

struct tagLevelInfo
{
	Image*		playerLevelUp;
	Image*		leftLevelUp;
	Animation*	playerAni;
	Animation*	leftAni;
	Image*		levelFrame;
	Vector3		pos;
	bool		active;		

	HRESULT init()
	{
		playerLevelUp = IMAGE_MANAGER->findImage("levelUp");
		leftLevelUp = IMAGE_MANAGER->findImage("levelUp");
		playerAni = new Animation;
		playerAni->init(playerLevelUp->getWidth(), playerLevelUp->getHeight(), 4, 1);
		playerAni->setDefPlayFrame();
		playerAni->setFPS(1);

		return S_OK;
	}
	void update(const Vector3& playerPos)
	{
		if (active)
		{
			playerAni->frameUpdate(TIME_MANAGER->getElapsedTime() * 10);	

			if (!playerAni->isPlay())
			{
				active = false;
			}
		}
	}
	void render()
	{
		if (active)
		{
			CAMERA_MANAGER->aniRender(playerLevelUp, pos, playerAni);
		}
	}
};

struct tagBossInfo
{	
	Image*			frameHp;	// ���� ü�� ������
	ProgressBar*	bossBar;	// ���� ü�� ���α׷�����
	float			currentHp;	// ���� ü��
	float			maxHp;		// �ִ� ü��
	Vector2			pos;		// ��ǥ
	bool			active;		// ��� �� ������Ʈ ����

	HRESULT init()
	{
		bossBar = new ProgressBar;
		frameHp = IMAGE_MANAGER->findImage("bossHpFrame");
		bossBar->init("bossBackBar", "bossFrontBar", Vector2(WINSIZEX / 2 - 70, WINSIZEY - 95), Vector2(-30.0f, 0.0f));	// ���� ü�� ��ġ����

		return S_OK;
	}
	void update()
	{
		if (active)
		{
			bossBar->update();
			bossBar->setGauge(currentHp, maxHp);
		}
	}
	void render()
	{
		if (active)
		{
			bossBar->render();
			frameHp->render(Vector2(WINSIZEX / 2, WINSIZEY - 100));
		}
	}
};

enum class DOOR_STATE
{
	LOCK, UNLOCK, SHOP	// ���, ����, ����
};

struct tagDoorInfo
{		
	DOOR_STATE door;
	Vector3 pos;
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
	tagPlayerInfo	_playerInfo;
	tagLevelInfo	_levelInfo;
	tagBossInfo		_bossInfo;
	tagCellPhone	_cellPhone;

	class GameObject* _player;

public:
	UIManager();
	~UIManager();

	HRESULT init(class GameObject* player);
	void release();
	void update();
	void render();	

	// �÷��̾� ü�� �� ����ġ
	void setPlayerHpActive(bool active) { _playerInfo.active = active; }
	void setPlayerHp(float currentHp, float maxHp) { _playerInfo.currentHp = currentHp; _playerInfo.maxHp = maxHp; }
	void setPlayerExp(float currentExp, float maxExp) { _playerInfo.currentExp = currentExp; _playerInfo.maxExp = maxExp; }

	void setLevelUp(bool active);	

	// ���� ü��
	void setBossHpActive(bool active) { _bossInfo.active = active; }
	void setBossHp(float currentHp, float maxHp) { _bossInfo.currentHp = currentHp; _bossInfo.maxHp = maxHp; }
};

