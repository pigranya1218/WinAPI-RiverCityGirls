#include "stdafx.h"
#include "StageManager.h"
#include "NormalStage.h"
#include "BossStage.h"

void StageManager::init()
{
	// ��� ������������ ������ ������ ���Ϸκ��� �а� ������ ����
	_currStage = new NormalStage;
	_currStage->init(IMAGE_MANAGER->findImage(""));
	_currStage->setStageManager(this);
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
}

void StageManager::render()
{
}
