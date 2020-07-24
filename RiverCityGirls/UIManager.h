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
			pos = playerPos;
			

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
	DOOR_STATE	doorState;	// ���� �� ����
	Vector3		pos;		// ��ǥ

	HRESULT init(DOOR_STATE state, const Vector3& doorPos)
	{
		doorState = state;
		pos = doorPos;
		scale = 0.7f;
		alpha = 1.0f;

		switch (doorState)
		{
			case DOOR_STATE::LOCK:
			{
				img = IMAGE_MANAGER->findImage("lockDoor"); 
				break;
			}
			case DOOR_STATE::UNLOCK:
			{
				img = IMAGE_MANAGER->findImage("unlockDoor");
				break;
			}			
			case DOOR_STATE::SHOP:
			{
				img = IMAGE_MANAGER->findImage("shopDoor");
				break;
			}			
		}
		
		return S_OK;
	}
	void update(const Vector3& playerPos)
	{
		float distance = Vector3::distance(pos, playerPos);

		switch (distance < 150.0f)
		{
			case 0:	// ���� �ִ�
			{
				// ������
				if (scale > 0.6f)
					scale -= 0.02f;
				else
					scale = 0.6f;
				// ���İ�
				if (alpha < 0.3f)
					alpha = 0.3f;
				else
					alpha -= 0.05f;

				break;
			}
			case 1:	// ���� ������
			{
				// ������
				if (scale < 0.8f)
					scale += 0.02f;
				else
					scale = 0.8f;
				// ���İ�
				if (alpha > 1.0f)
					alpha = 1.0f;
				else
					alpha += 0.05f;

				break;
			}
		}		
	}
	void render()
	{
		img->setAlpha(alpha);
		img->setScale(scale);
		CAMERA_MANAGER->render(img, CAMERA_MANAGER->convertV3ToV2(pos));
	}

private:
	Image*		img;		// �̹���
	float		scale;		// ������
	float		alpha;		// ���İ�
};

struct tagCloseInfo
{
	bool	active;	// ��� ����
	HRESULT init()
	{
		img = IMAGE_MANAGER->findImage("closeUp");
		active = 0;
		scale = 2.0f;

		return S_OK;
	}
	void update()
	{
		if (active)
		{
			scale -= 0.01f;
			if (scale < 0.2f)
			{
				active = false;
				scale = 2.0f;
			}
		}		
	}
	void render(const Vector3& playerPos)
	{
		if (active)
		{
			img->setScale(scale);
			img->render(CAMERA_MANAGER->getRelativeV2(CAMERA_MANAGER->convertV3ToV2(playerPos)));
		}
	}

private:
	Image*	img;	// ��Ʈ
	float	scale;	// ������	
};

struct tagShopInfo
{
	float money;
	bool active;
	int currentList;
	FloatRect itemPos;

	HRESULT init()
	{
		currentList = 0;
		return S_OK;
	}
	void update()
	{
		if (active)
		{
			
		}
	}
	void render()
	{
		if (active)
		{
			IMAGE_MANAGER->findImage("shopFrame")->setSize(Vector2(WINSIZEX, WINSIZEY));
			IMAGE_MANAGER->findImage("shopFrame")->render(Vector2(WINSIZEX / 2, WINSIZEY / 2));
		}
	}
};

// ���ڰ� ���� ���� �ڹ��谡 �μ���
enum class LOCK_STATE : int
{
	LOCK_4 = 4,		
	LOCK_3 = 3,
	LOCK_2 = 2,
	LOCK_1 = 1,
	LOCK_0 = 0,
	NORMAL = -1
};

struct tagLockInfo
{	
private:
	struct tagChainInfo
	{	
	private:
		Image*		img;
		Vector2		pos;
		Vector2		size;
		Animation*	ani;

		float fps;

	public:
		HRESULT init(const string imageName, const Vector2& position, const Vector2& setSize)
		{
			img = IMAGE_MANAGER->findImage(imageName);

			pos = position;
			size = setSize;

			ani = new Animation;
			ani->init(img->getWidth(), img->getHeight(), img->getMaxFrameX(), img->getMaxFrameY());
			ani->setDefPlayFrame();
			ani->setFPS(1);
			ani->start();

			return S_OK;
		}
		void update()
		{
			ani->frameUpdate(TIME_MANAGER->getElapsedTime() * 10);
		}
		void render()
		{
			img->setSize(size);
			img->aniRender(pos, ani);
		}
	};
	
	tagChainInfo chainLeft, chainRight;
	tagChainInfo chainTop, chainBottom;

	Image*		img;
	Animation*	ani;
	Vector2		pos;

	LOCK_STATE	curState;

	bool active;

	void chainSetting(string lockSt)
	{
		chainTop.init(
			lockSt + "_top",
			Vector2(WINSIZEX / 2.0f, 100 + IMAGE_MANAGER->findImage(lockSt + "_top")->getFrameSize().y / 2),
			Vector2((float)WINSIZEX, IMAGE_MANAGER->findImage(lockSt + "_top")->getFrameSize().y)
		);

		chainBottom.init(
			lockSt + "_bot",
			Vector2(WINSIZEX / 2.0f, WINSIZEY - (100 + (IMAGE_MANAGER->findImage(lockSt + "_bot")->getFrameSize().y / 2))),
			Vector2((float)WINSIZEX, IMAGE_MANAGER->findImage(lockSt + "_bot")->getFrameSize().y)
		);

		chainLeft.init(
			lockSt + "_left",
			Vector2(IMAGE_MANAGER->findImage(lockSt + "_left")->getFrameSize().x / 2, WINSIZEY / 2.0f),
			Vector2(IMAGE_MANAGER->findImage(lockSt + "_left")->getFrameSize().x, (float)WINSIZEY - 200)
		);

		chainRight.init(
			lockSt + "_right",
			Vector2(WINSIZEX - (IMAGE_MANAGER->findImage(lockSt + "_right")->getFrameSize().x / 2), (WINSIZEY) / 2.0f),
			Vector2(IMAGE_MANAGER->findImage(lockSt + "_right")->getFrameSize().x, (float)WINSIZEY - 200)
		);
	}

public:	

	void init(LOCK_STATE state)
	{		
		if (state == LOCK_STATE::NORMAL) return;

		else if (state == curState) return;
		switch (state)
		{
			case LOCK_STATE::LOCK_4: case LOCK_STATE::LOCK_3: 
			case LOCK_STATE::LOCK_2: case LOCK_STATE::LOCK_1:
			{
				if(active) break;

				active = true;
				chainSetting("chainLock");
				break;
			}
			case LOCK_STATE::LOCK_0:
			{								
				chainSetting("chainUnlock");
				break;
			}			
		}		
		
		switch (state)
		{
			case LOCK_STATE::LOCK_4: img = IMAGE_MANAGER->findImage("lock_4"); break;
			case LOCK_STATE::LOCK_3: img = IMAGE_MANAGER->findImage("lock_3"); break;
			case LOCK_STATE::LOCK_2: img = IMAGE_MANAGER->findImage("lock_2"); break;
			case LOCK_STATE::LOCK_1: img = IMAGE_MANAGER->findImage("lock_1"); break;
			case LOCK_STATE::LOCK_0: img = IMAGE_MANAGER->findImage("lock_0"); break;
		}
		
		ani = new Animation;
		ani->init(img->getWidth(), img->getHeight(), img->getMaxFrameX(), img->getMaxFrameY());
		ani->setDefPlayFrame();
		ani->setFPS(1);
		ani->start();
		

		curState = state;

		pos = Vector2(WINSIZEX / 2.0f, 120 + img->getFrameSize().x / 2);		
	}
	void update()
	{
		if (active)
		{
			chainLeft.update(); 
			chainRight.update();
			chainTop.update(); 
			chainBottom.update();	

			ani->frameUpdate(TIME_MANAGER->getElapsedTime() * 10);

			if (curState == LOCK_STATE::LOCK_0 && !ani->isPlay())
			{
				curState = LOCK_STATE::NORMAL;
				active = false;
			}
		}
	}
	void render()
	{
		if (active)
		{
			chainLeft.render(); 
			chainRight.render();
			chainTop.render(); 
			chainBottom.render();

			img->aniRender(pos, ani);
		}
	}
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
	tagCloseInfo	_close;
	tagShopInfo		_shop;	
	tagLockInfo		_lock;

	vector<tagDoorInfo> _vDoor;

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

	// ������ ���
	void setLevelUp(bool active);	

	// ���� ü��
	void setBossHpActive(bool active) { _bossInfo.active = active; }
	void setBossHp(float currentHp, float maxHp) { _bossInfo.currentHp = currentHp; _bossInfo.maxHp = maxHp; }

	// �� ����
	void setDoor(vector<tagDoorInfo> doors);

	void setCloseUp(bool active) { _close.active = active; }

	void setShopUI(bool active) { _shop.active = active; }

	void setLock(LOCK_STATE state);
};

