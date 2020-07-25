#include "stdafx.h"
#include "StageManager.h"
#include "StartStage.h"
#include "MiddleStage.h"
#include "BossStage.h"


void StageManager::init()
{
	Stage* stage_1 = new StartStage;
	stage_1->setStageManager(this);
	stage_1->setPlayer(_player);
	stage_1->init(IMAGE_MANAGER->findImage("STAGE_1"), 3);

	_stageMap["START_STAGE"] = stage_1;

	Stage* stage_2 = new MiddleStage;
	stage_2->setStageManager(this);
	stage_2->setPlayer(_player);
	stage_2->init(IMAGE_MANAGER->findImage("STAGE_2"), 3);
	_stageMap["MIDDLE_STAGE"] = stage_2;

	Stage* stage_3 = new BossStage;
	stage_3->setStageManager(this);
	stage_3->setPlayer(_player);
	stage_3->init(IMAGE_MANAGER->findImage("STAGE_BOSS_BEFORE"), 3);
	_stageMap["BOSS_STAGE"] = stage_3;

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
	if (!_dgManager->getIsPlay() && !_uiManager->getShopUI())
	{
		if (_stageBuffer != nullptr)
		{
			_currStage = _stageBuffer;
			_currStage->enter();
		}

		_stageBuffer = _currStage->update();
		_player->update();
	}
}

void StageManager::render()
{
	_currStage->render();
	_player->render();
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

void StageManager::openShop()
{
	_uiManager->setShopUI(true);
}

void StageManager::startDialogue(BossChapter keyname)
{
	_dgManager->startChapter(keyname);
}
