#include "stdafx.h"
#include "enemyManager.h"
#include "SchoolBoy.h"
#include "SchoolGirl.h"
#include "CheerGirl.h"
#include "Boss.h"
#include "enemy.h"
#include "stage.h"


HRESULT EnemyManager::init()
{
	_schoolBoy = new SchoolBoy;
	_schoolBoy->init();
	_schoolBoy->setEnemyManager(this);

	_schoolGirl = new SchoolGirl;
	_schoolGirl->init();
	_schoolGirl->setEnemyManager(this);

	_cheerGirl = new CheerGirl;
	_cheerGirl->init();
	_cheerGirl->setEnemyManager(this);

	_boss = new Boss;
	_boss->init();
	_boss->setEnemyManager(this);

	return S_OK;
}

void EnemyManager::release()
{
}

void EnemyManager::update()
{
	_schoolBoy->update();
	_schoolGirl->update();
	_cheerGirl->update();
	_boss->update();
}

void EnemyManager::render()
{

	_schoolBoy->render();
	_cheerGirl->render();	
	_schoolGirl->render();
	_boss->render();
	
}

void EnemyManager::setEnemy()
{
}

void EnemyManager::removeEnemy(int arrNum)
{
}

void EnemyManager::moveEnemy(GameObject * enemy, Vector3 dir)
{
	_stage->moveGameObject(enemy, dir);
}

Vector3 EnemyManager::getPlayerPosition()
{
	return _stage->getPlayerPosition();
}