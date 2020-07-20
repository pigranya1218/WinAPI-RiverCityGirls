#include "stdafx.h"
#include "enemyManager.h"
#include "enemy.h"

HRESULT EnemyManager::init()
{
	_schoolBoy = new SchoolBoy;
	_schoolBoy->init();

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
