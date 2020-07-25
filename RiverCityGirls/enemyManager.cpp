#include "stdafx.h"
#include "enemyManager.h"
#include "SchoolBoy.h"
#include "SchoolGirl.h"
#include "CheerGirl.h"
#include "Boss.h"
#include "enemy.h"
#include "stage.h"

void EnemyManager::init()
{

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
	for (int i = 0; i < _enemies.size();)
	{
		_enemies[i]->update();
		if (!_enemies[i]->isActive())
		{
			_enemies[i]->release();
			delete _enemies[i];
			_enemies.erase(_enemies.begin() + i);
		}
		else
		{
			i++;
		}
	}
}

void EnemyManager::render()
{
	
	for (int i = 0; i < _enemies.size() ; i++)
	{
		_enemies[i]->render();
	}
}

void EnemyManager::moveEnemy(GameObject * enemy, Vector3 dir)
{
	_stage->moveGameObject(enemy, dir);

}

void EnemyManager::spawnEnemy(ENEMY_TYPE type, Vector2 pos)
{
	switch (type)
	{
	case ENEMY_TYPE::SCHOOL_BOY:
	{
		SchoolBoy* _schoolBoy = new SchoolBoy;
		_schoolBoy->init();
		_schoolBoy->setEnemyManager(this);
		_schoolBoy->setPosition(Vector3(pos.x, -_schoolBoy->getSize().y / 2, pos.y));
		_enemies.push_back(_schoolBoy);
	}
	break;
	case ENEMY_TYPE::SCHOOL_GIRL:
	{
		SchoolGirl* _schoolGirl = new SchoolGirl;
		_schoolGirl->init();
		_schoolGirl->setEnemyManager(this);
		_schoolGirl->setPosition(Vector3(pos.x, -_schoolGirl->getSize().y / 2, pos.y));
		_enemies.push_back(_schoolGirl);
	}
	break;
	case ENEMY_TYPE::CHEER_GIRL:
	{
		CheerGirl* _cheerGirl = new CheerGirl;
		_cheerGirl->init();
		_cheerGirl->setEnemyManager(this);
		_cheerGirl->setPosition(Vector3(pos.x, -_cheerGirl->getSize().y / 2, pos.y));
		_enemies.push_back(_cheerGirl);
	}
	break;
	case ENEMY_TYPE::BOSS:
	{
		Boss* _boss = new Boss;
		_boss->init();
		_boss->setEnemyManager(this);
		_boss->setPosition(Vector3(pos.x, -_boss->getSize().y / 2, pos.y));
		_enemies.push_back(_boss);
	}
	break;
	}
}

void EnemyManager::clearEnemy()
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->release();
		delete _enemies[i];
	}
	_enemies.clear();
}

Vector3 EnemyManager::getPlayerPosition()
{
	return _stage->getPlayerPosition();
}

float EnemyManager::getCenterBottom(Vector3 pos)
{
	return _stage->getCenterBottom(pos);
}

void EnemyManager::getHit(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->getHit(hitter, attackRc, damage, type);
	}
}

void EnemyManager::enemyAttack(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	vector<OBJECT_TEAM> getAttack;
	getAttack.push_back(OBJECT_TEAM::PLAYER);
	getAttack.push_back(OBJECT_TEAM::OBJECT);
	_stage->attack(hitter, attackRc, damage, type, getAttack);
}