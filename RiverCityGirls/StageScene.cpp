#include "stdafx.h"
#include "StageScene.h"

HRESULT StageScene::init()
{
	_stageManager = new StageManager;

	_uiManager = new UIManager;

	_player = new Player;

	_stageManager->setUIManager(_uiManager);
	_stageManager->setPlayer(_player);

	_stageManager->init();
	_uiManager->init();
	_player->init();

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
}

void StageScene::render()
{
	_stageManager->render();
	_player->render();
	_uiManager->render();
}
