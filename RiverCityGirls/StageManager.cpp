#include "stdafx.h"
#include "StageManager.h"
#include "NormalStage.h"
#include "BossStage.h"


void StageManager::init()
{
	// ��� ������������ ������ ������ ���Ϸκ��� �а� ������ ����
	
	// DEBUG
	_currStage = new NormalStage;
	_currStage->init(IMAGE_MANAGER->findImage("STAGE_1"), 3);
	_currStage->setStageManager(this);
	_currStage->setPlayer(_player);
}

void StageManager::release()
{
}

void StageManager::update()
{
	Stage* newStage = _currStage->update();
	if (newStage != nullptr)
	{
		_currStage->exit();
		_currStage = newStage;
		_currStage->enter();
	}

	CAMERA_MANAGER->setXY(CAMERA_MANAGER->convertV3ToV2(_player->getPosition()));
}

void StageManager::render()
{
	_currStage->render();
	
}
