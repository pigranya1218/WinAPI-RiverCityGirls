#include "stdafx.h"
#include "enemyManager.h"
#include "SchoolBoy.h"
#include "enemy.h"
#include "stage.h"


HRESULT EnemyManager::init()
{
	_schoolBoy = new SchoolBoy;
	_schoolBoy->init();
	_schoolBoy->setEnemyManager(this);

	return S_OK;
}

void EnemyManager::release()
{
}

void EnemyManager::update()
{
	_schoolBoy->update();
}

void EnemyManager::render()
{
	_schoolBoy->render();
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