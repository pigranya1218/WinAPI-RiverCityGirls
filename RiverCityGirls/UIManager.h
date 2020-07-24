#pragma once
#include "ProgressBar.h"

#define PLAYERHPMAX 23
#define DOORMAX 3

struct tagPlayerInfo
{	
	Image*	frameHp;	// 체력 프레임
	Image*	hpDigit;	// 체력 한칸 이미지
	float	currentHp;	// 현재 체력
	float	maxHp;		// 최대 체력	
	Vector2 pos;		// 좌표
	bool	active;		// 출력 및 업데이트 여부
	int		digitNum;	// 체력 칸 개수

	// 경험치 관련
	ProgressBar* expBar;		// 경험치 막대
	float		 currentExp;	// 현재 경험치
	float		 maxExp;		// 최대 경험치

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
			digitNum = (int)((currentHp / maxHp) * PLAYERHPMAX);	// 체력바 갯수 설정

			// 체력바는 0개인데 체력은 아직 남아있는 경우
			if (!digitNum && currentHp)
			{
				digitNum = 1;	// 체력바는 1로 만들어줌
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
	Image*			frameHp;	// 보스 체력 프레임
	ProgressBar*	bossBar;	// 보스 체력 프로그레스바
	float			currentHp;	// 현재 체력
	float			maxHp;		// 최대 체력
	Vector2			pos;		// 좌표
	bool			active;		// 출력 및 업데이트 여부

	HRESULT init()
	{
		bossBar = new ProgressBar;
		frameHp = IMAGE_MANAGER->findImage("bossHpFrame");
		bossBar->init("bossBackBar", "bossFrontBar", Vector2(WINSIZEX / 2 - 70, WINSIZEY - 95), Vector2(-30.0f, 0.0f));	// 보스 체력 위치설정

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
	LOCK, UNLOCK, SHOP	// 잠금, 열림, 상점
};

struct tagDoorInfo
{		
	DOOR_STATE	doorState;	// 현재 문 상태
	Vector3		pos;		// 좌표

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
			case 0:	// 문과 멀다
			{
				// 스케일
				if (scale > 0.6f)
					scale -= 0.02f;
				else
					scale = 0.6f;
				// 알파값
				if (alpha < 0.3f)
					alpha = 0.3f;
				else
					alpha -= 0.05f;

				break;
			}
			case 1:	// 문과 가깝다
			{
				// 스케일
				if (scale < 0.8f)
					scale += 0.02f;
				else
					scale = 0.8f;
				// 알파값
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
	Image*		img;		// 이미지
	float		scale;		// 스케일
	float		alpha;		// 알파값
};

struct tagCloseInfo
{
	bool	active;	// 출력 여부
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
	Image*	img;	// 하트
	float	scale;	// 스케일	
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

	vector<tagDoorInfo> _vDoor;

	class GameObject* _player;

public:
	UIManager();
	~UIManager();

	HRESULT init(class GameObject* player);
	void release();
	void update();
	void render();	

	// 플레이어 체력 및 경험치
	void setPlayerHpActive(bool active) { _playerInfo.active = active; }
	void setPlayerHp(float currentHp, float maxHp) { _playerInfo.currentHp = currentHp; _playerInfo.maxHp = maxHp; }
	void setPlayerExp(float currentExp, float maxExp) { _playerInfo.currentExp = currentExp; _playerInfo.maxExp = maxExp; }

	// 레벨업 출력
	void setLevelUp(bool active);	

	// 보스 체력
	void setBossHpActive(bool active) { _bossInfo.active = active; }
	void setBossHp(float currentHp, float maxHp) { _bossInfo.currentHp = currentHp; _bossInfo.maxHp = maxHp; }

	// 문 세팅
	void setDoor(vector<tagDoorInfo> doors);

	void setCloseUp(bool active) { _close.active = active; }

	void setShopUI(bool active) { _shop.active = active; }
};

