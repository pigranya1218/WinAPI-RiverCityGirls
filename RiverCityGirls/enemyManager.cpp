#include "stdafx.h"
#include "enemyManager.h"
#include "SchoolBoy.h"
#include "SchoolGirl.h"
#include "CheerGirl.h"
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
}

void EnemyManager::render()
{
	_schoolBoy->render();
	_schoolGirl->render();
	_cheerGirl->render();
}

void EnemyManager::setEnemy()
{
}

void EnemyManager::removeEnemy(int arrNum)
{
}

void EnemyManager::moveEnemy(GameObject * enemy, Vector3 dir)
{
	_stage->moveGameObject(*enemy, dir);
}

Vector3 EnemyManager::getPlayerPosition()
{
	return _stage->getPlayerPosition();
}