#include "stdafx.h"
#include "Enemy.h"
#include "EnemyManager.h"

void Enemy::init()
{
}

void Enemy::release()
{
}

void Enemy::update()
{
}

void Enemy::render()
{
	
}

void Enemy::getHit(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	// 1. Z축 검사
	Vector3 hitterPos = hitter->getPosition();
	Vector3 hitterSize = hitter->getSize();
	float hitterMinZ = hitterPos.z - (hitterSize.z / 2);
	float hitterMaxZ = hitterPos.z + (hitterSize.z / 2);
	float victimMinZ = _position.z - (_size.z / 2);
	float victimMaxZ = _position.z + (_size.z / 2);
	if (victimMaxZ < hitterMinZ || hitterMaxZ < victimMinZ) // Z 축 좌표가 공유되지 않는 경우 종료
	{
		return;
	}

	// 2. X, Y 검사 (IntersectRect)
	FloatRect victimRc = FloatRect(_position.x - (_size.x / 2), _position.y - (_size.y / 2), _position.x + (_size.x / 2), _position.y + (_size.y / 2));
	if (FloatRect::intersect(victimRc, attackRc))
	{
		hitEffect(hitter, attackRc, damage, type);
	}
}

void Enemy::enemyAttack(FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	_enemyManager->enemyAttack(this, attackRc, damage, type);
}

void Enemy::hitEffect(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type)
{

}

void Enemy::attack(FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	_enemyManager->enemyAttack(this, attackRc, damage, type);
}

void Enemy::setDirectionToPlayer()
{
	Vector3 playerPos = _enemyManager->getPlayerPosition();
	if (playerPos.x <= _position.x - 50)
	{
		_direction = DIRECTION::LEFT;
	}
	else if (playerPos.x >= _position.x + 50)
	{
		_direction = DIRECTION::RIGHT;
	}
}

