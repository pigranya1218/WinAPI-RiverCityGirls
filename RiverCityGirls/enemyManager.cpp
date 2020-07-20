#include "stdafx.h"
#include "enemyManager.h"
#include "enemy.h"

HRESULT enemyManager::init()
{
	_schoolBoy = new schoolBoy;
	_schoolBoy->init();

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	_schoolBoy->update();
}

void enemyManager::render()
{
	_schoolBoy->render();
}

void enemyManager::setEnemy()
{
}

void enemyManager::removeEnemy(int arrNum)
{
}
