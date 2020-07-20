#include "stdafx.h"
#include "StageManager.h"
#include "NormalStage.h"
#include "BossStage.h"

void StageManager::init()
{
	// 모든 스테이지들의 정보를 데이터 파일로부터 읽고 맵으로 관리
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
