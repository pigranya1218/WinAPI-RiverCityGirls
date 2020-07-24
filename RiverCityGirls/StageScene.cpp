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

	_player->init();
	_stageManager->init();
	_dgManager->init(0.8f);
	_uiManager->init(_player);

	// UI 테스트입니다
	//_uiManager->setPlayerHpActive(true);		
	//_uiManager->setShopUI(true);
	
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
	hp -= 2.1f;
	if (hp < 0)
	{
		hp = 100.0f;
		_uiManager->setLevelUp(true);
		//_uiManager->setCloseUp(true);
	}
	_uiManager->setPlayerHp(hp, 100.0f);
	_uiManager->setBossHp(hp, 100.0f);	
	_uiManager->setPlayerExp(hp, 100.0f);
}

void StageScene::render()
{
	_stageManager->render();
	_player->render();

	CAMERA_MANAGER->renderZList();

	_uiManager->render();
	_dgManager->render();

}
