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
	//_schoolBoy = new SchoolBoy;
	//_schoolBoy->init();
	//_schoolBoy->setEnemyManager(this);
	//_enemies.push_back(_schoolBoy);
	//
	//_schoolGirl = new SchoolGirl;
	//_schoolGirl->init();
	//_schoolGirl->setEnemyManager(this);
	//_enemies.push_back(_schoolGirl);

	_cheerGirl = new CheerGirl;
	_cheerGirl->init();
	_cheerGirl->setEnemyManager(this);
	_enemies.push_back(_cheerGirl);

	/*_boss = new Boss;
	_boss->init();
	_boss->setEnemyManager(this);
	_enemies.push_back(_boss);*/

	return S_OK;
}

void EnemyManager::release()
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->release();
		delete _enemies[i];
	}
	_enemies.clear();
}

void EnemyManager::update()
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->update();
	}
}

void EnemyManager::render()
{

	for (int i = 0; i < _enemies.size() ; i++)
	{
		_enemies[i]->render();
	}
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

void EnemyManager::getHit(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->getHit(hitter, attackRc, damage, type);
	}
}
