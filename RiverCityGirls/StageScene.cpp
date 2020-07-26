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

	// UI 테스트입니다
	_uiManager->setPlayerHpActive(true);
	_uiManager->setHart(true);
	

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
	EFFECT_MANAGER->update();
	
	_uiManager->update();
	_dgManager->update();	

	if (KEY_MANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		EFFECT_MANAGER->play("effect_5", _ptMouse.x, _ptMouse.y);
	}

	EFFECT_MANAGER->update();
}

void StageScene::render()
{
	_stageManager->render();
	EFFECT_MANAGER->render();

	CAMERA_MANAGER->renderZList();

	_uiManager->render();
	_dgManager->render();	

	EFFECT_MANAGER->render();
}
