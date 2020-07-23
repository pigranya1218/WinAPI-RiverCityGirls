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
}

void StageManager::render()
{
	_currStage->render();
	
}

void StageManager::playerAttack(Vector3 position, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	vector<OBJECT_TEAM> getAttack;
	getAttack.push_back(OBJECT_TEAM::ENEMY);
	getAttack.push_back(OBJECT_TEAM::OBJECT);
	_currStage->attack(position, attackRc, damage, type, getAttack);
}
