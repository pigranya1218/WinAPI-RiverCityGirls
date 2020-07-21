#include "stdafx.h"
#include "enemyManager.h"
#include "enemy.h"

HRESULT EnemyManager::init()
{
	_schoolBoy = new SchoolBoy;
	_schoolBoy->init();

	_SchoolGirl = new SchoolGirl;
	_SchoolGirl->init();

	return S_OK;
}

void EnemyManager::release()
{
}

void EnemyManager::update()
{
	_schoolBoy->update();
	_SchoolGirl->update();
}

void EnemyManager::render()
{
	_schoolBoy->render();
	_SchoolGirl->render();
}

void EnemyManager::setEnemy()
{
}

void EnemyManager::removeEnemy(int arrNum)
{
}
