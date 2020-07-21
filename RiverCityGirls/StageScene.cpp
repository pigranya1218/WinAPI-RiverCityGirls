#include "stdafx.h"
#include "StageScene.h"

HRESULT StageScene::init()
{
	_stageManager = new StageManager;

	_uiManager = new UIManager;

	_player = new Player;

	_dgManager = new DialogueManager;

	_stageManager->setUIManager(_uiManager);
	_stageManager->setPlayer(_player);
	_player->setStageManager(_stageManager);

	_stageManager->init();
	_uiManager->init();
	_player->init();
	_dgManager->init();

	// UI 테스트입니다
	_uiManager->setPlayerHpActive(true);
	_uiManager->setPlayerHp(100.0f, 100.0f);

	_uiManager->setBossHpActive(true);
	_uiManager->setBossHp(100.0f, 100.0f);
	
	// 다이얼로그 테스티입니다.
	_dgManager->startChapter(BossChapter::BATTLE_BEFORE);

	return S_OK;
}

void StageScene::release()
{
	_stageManager->release();
	SAFE_DELETE(_stageManager);
}

void StageScene::update()
{
	_stageManager->update();
	_player->update();
	_uiManager->update();

	//
	_dgManager->update();

	// UI 테스트입니다.
	static float hp = 100.0f;
	hp -= 0.1f;
	if (hp < 0)hp = 100.0f;
	_uiManager->setPlayerHp(hp, 100.0f);
	_uiManager->setBossHp(hp, 100.0f);
	//_uiManager->setDoorLock(0, true, Vector2(WINSIZEX / 2, WINSIZEY / 2), currentDoor::UNLOCK);
	
}

void StageScene::render()
{
	_stageManager->render();
	_player->render();
	_uiManager->render();
	//_dgManager->render();

	CAMERA_MANAGER->renderZList();
}
