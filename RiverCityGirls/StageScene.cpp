#include "stdafx.h"
#include "StageScene.h"

HRESULT StageScene::init()
{
	_stageManager = new StageManager;

	_uiManager = new UIManager;

	_player = new Player;

	_dgManager = new DialogueManager;

	_stageManager->setUIManager(_uiManager);
	_stageManager->setDialogueManager(_dgManager);
	_stageManager->setPlayer(_player);
	_player->setStageManager(_stageManager);

	_player->init();
	_stageManager->init();
	_dgManager->init(1);
	_uiManager->init(_player);

	//_uiManager->setShopUI(true);

	// UI 테스트입니다
	//_uiManager->setPlayerHpActive(true);				

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
	CAMERA_MANAGER->processEvent();
	// _player->update();
	_uiManager->update();

	//
	_dgManager->update();

	// UI 테스트입니다.
	/*static float hp = 100.0f;	
	static int tt = 4;
	hp -= 1.0f;
	if (hp < 0)
	{
		hp = 100.0f;
		_uiManager->setLevelUp(true);	
		_uiManager->setLock((LOCK_STATE)tt--);
	}
	_uiManager->setPlayerHp(hp, 100.0f);	*/
}

void StageScene::render()
{
	_stageManager->render();
	// _player->render();

	CAMERA_MANAGER->renderZList();

	_uiManager->render();
	_dgManager->render();

}
