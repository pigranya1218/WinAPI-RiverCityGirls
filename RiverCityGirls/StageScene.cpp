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

	// UI �׽�Ʈ�Դϴ�
	_uiManager->setPlayerHpActive(true);

	

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
	_dgManager->update();	
}

void StageScene::render()
{
	_stageManager->render();
	// _player->render();

	CAMERA_MANAGER->renderZList();

	_uiManager->render();
	_dgManager->render();	
}
