#include "stdafx.h"
#include "StageManager.h"
#include "StartStage.h"
#include "MiddleStage.h"
#include "BossStage.h"


void StageManager::init()
{
	Stage* Stage_1 = new StartStage;
	Stage_1->setStageManager(this);
	Stage_1->setPlayer(_player);
	Stage_1->init(IMAGE_MANAGER->findImage("STAGE_1"), 3);

	_stageMap["START_STAGE"] = Stage_1;

	Stage* Stage_2 = new MiddleStage;
	Stage_2->setStageManager(this);
	Stage_2->setPlayer(_player);
	Stage_2->init(IMAGE_MANAGER->findImage("STAGE_1"), 3);
	_stageMap["MIDDLE_STAGE"] = Stage_2;

	Stage* Stage_3 = new BossStage;
	Stage_3->setStageManager(this);
	Stage_3->setPlayer(_player);
	Stage_3->init(IMAGE_MANAGER->findImage("STAGE_1"), 3);
	_stageMap["BOSS_STAGE"] = Stage_3;

	_currStage = _stageMap["START_STAGE"];
	_currStage->enter();
}

void StageManager::release()
{
	for (auto iter = _stageMap.begin(); iter != _stageMap.end(); iter++)
	{
		iter->second->exit();
		delete iter->second;
	}
	_stageMap.clear();
}
 
void StageManager::update()
{
	Stage* newStage = _currStage->update();
	if (newStage != nullptr)
	{
		_currStage = newStage;
	}
}

void StageManager::render()
{
	_currStage->render();
}

void StageManager::playerAttack(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	vector<OBJECT_TEAM> getAttack;
	getAttack.push_back(OBJECT_TEAM::ENEMY);
	getAttack.push_back(OBJECT_TEAM::OBJECT);
	_currStage->attack(hitter, attackRc, damage, type, getAttack);
}

void StageManager::setDoorInfo(vector<tagDoorInfo> doorInfos)
{
	_uiManager->setDoor(doorInfos);
}
