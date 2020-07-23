#include "stdafx.h"
#include "Stage.h"
#include "StageManager.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#include "Player.h"


void Stage::init(Image * background, float bgScale)
{
	_background = background;
	_bgScale = bgScale;
	float maxWidth = _background->getWidth() * _bgScale;
	float maxHeight = _background->getHeight() * _bgScale;
	CAMERA_MANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, maxWidth - WINSIZEX, maxHeight - WINSIZEY );

	_objectManager = new ObjectManager;
	_objectManager->init();

	//Object ��ġ
	_objectManager->spawnObject(OBJECT_TYPE::DESK01, Vector3(460, 0, 510), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::DESK02, Vector3(710, 0, 510), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::DESK01, Vector3(970, 0, 510), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::DESK03, Vector3(1230, 0, 510), DIRECTION::LEFT);

	_objectManager->spawnObject(OBJECT_TYPE::mrRudis, Vector3(1670, 0, 510), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::schoolBoyA_idle01, Vector3(600, 0, 400), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::schoolGirlB_idle02, Vector3(500, 0, 400), DIRECTION::RIGHT);
	_objectManager->spawnObject(OBJECT_TYPE::SNACKMACHINE, Vector3(900, 0, 407), DIRECTION::LEFT);

	_enemyManager = new EnemyManager;
	_enemyManager->setStage(this);
	_enemyManager->init();
}

void Stage::enter()
{
}

void Stage::exit()
{
	_objectManager->release();
	_enemyManager->release();
	for (int i = 0; i < _restrictLines.size(); i++)
	{
		delete _restrictLines[i];
	}
	_restrictLines.clear();
}

Stage * Stage::update()
{
	return nullptr;
}

void Stage::render()
{
}

// ���� ������Ʈ�� �̵������� �������� �̵��� �� �ֵ��� �ϴ� �Լ�
void Stage::moveGameObject(GameObject* gameObject, Vector3 move)
{
	if (move.x == 0 && move.y == 0 && move.z == 0) return;

	float dir[4][2] = { {-1.0, -1.0}, {-1.0, 1.0}, {1.0, -1.0}, {1.0, 1.0} }; // �� �밢 ��
	float width = gameObject->getSize().x * 0.5; // �浹 ���� ����
	float height = gameObject->getSize().z * 0.5; // �浹 ���� ����

	Vector3 newPos = gameObject->getPosition() + move;
	Vector3 size = gameObject->getSize();
	if (newPos.y + (size.y / 2) > 0)
	{
		newPos.y = -(size.y / 2);
	}

	Vector3 newPoses[4]; // ���ο� ��ǥ�� �������� �ϴ� �밢 ��ġ
	for (int i = 0; i < 4; i++)
	{
		newPoses[i] = Vector3(newPos.x + dir[i][0] * width, newPos.y, newPos.z + dir[i][1] * height);
	}

	_objectManager->collision(newPoses, gameObject);

	// ���а��� �̵����� �񱳴� x, z ��
	for (int i = 0; i < _restrictLines.size(); i++)
	{
		_restrictLines[i]->checkCollision(newPoses, size);
	}

	// ��ü���� �̵����� �񱳴� x, y, z ��, ��ü�� �ö�Ż ���� ����
	
	newPos = Vector3(0, 0, 0);
	for (int i = 0; i < 4; i++)
	{
		newPos.x += newPoses[i].x;
		newPos.y += newPoses[i].y;
		newPos.z += newPoses[i].z;
	}
	newPos.x /= 4;
	newPos.y /= 4;
	newPos.z /= 4;

	gameObject->setPosition(newPos);
}

void Stage::attack(GameObject* hitter, FloatRect rc, float damage, ATTACK_TYPE type, vector<OBJECT_TEAM> getAttack)
{
	for (int i = 0; i < getAttack.size(); i++)
	{
		switch (getAttack[i])
		{
		case OBJECT_TEAM::PLAYER:
		{
			
		}
		break;
		case OBJECT_TEAM::ENEMY:
		{
			_enemyManager->getHit(hitter, rc, damage, type);
		}
		break;
		case OBJECT_TEAM::OBJECT:
		{
			_objectManager->getHit(hitter, rc, damage, type);
		}
		break;
		}
	}
}

Vector3 Stage::getPlayerPosition()
{
	return _player->getPosition();
	

}

