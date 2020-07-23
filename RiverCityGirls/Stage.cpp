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
	//CAMERA_MANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 1000, 1000);
	CAMERA_MANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, maxWidth - WINSIZEX, maxHeight - WINSIZEY);

	int linePos[4][4] = { {0, 670, _background->getWidth() * _bgScale, 670}, // 하
							{0, 380, _background->getWidth() * _bgScale, 380}, // 상
						{_background->getWidth() * _bgScale, 770, _background->getWidth() * _bgScale - 770, 0}, // 우
						{0, 740, 740, 0}}; // 좌
	LINEAR_VALUE_TYPE lineTypes[4] = {LINEAR_VALUE_TYPE::DOWN,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::UP};
	float lineRange[4][4] = { {70, _background->getWidth() * _bgScale - 100} , // 하
								{360, 1625}, // 상
								{1625, _background->getWidth() * _bgScale - 100}, // 좌
								{70, 360}}; // 우
	for (int i = 0; i < 4; i++)
	{
		LinearFunc line = LinearFunc::getLinearFuncFromPoints(Vector2(linePos[i][0], linePos[i][1]), Vector2(linePos[i][2], linePos[i][3]));
		_restrictLines.push_back(new RestrictMoveLine(line, lineTypes[i], lineRange[i][0], lineRange[i][1]));
	}

	_objectManager = new ObjectManager;
	_objectManager->init();

	//Object 배치
	_objectManager->spawnObject(OBJECT_TYPE::DESK, Vector3(460, 0, 510), DIRECTION::LEFT, 1);
	_objectManager->spawnObject(OBJECT_TYPE::DESK, Vector3(710, 0, 510), DIRECTION::LEFT, 2);
	_objectManager->spawnObject(OBJECT_TYPE::DESK, Vector3(970, 0, 510), DIRECTION::LEFT, 3);
	_objectManager->spawnObject(OBJECT_TYPE::DESK, Vector3(1230, 0, 510), DIRECTION::LEFT, 2);

	_objectManager->spawnObject(OBJECT_TYPE::DESK, Vector3(460, 0, 700), DIRECTION::LEFT, 4);
	_objectManager->spawnObject(OBJECT_TYPE::DESK, Vector3(710, 0, 700), DIRECTION::LEFT, 5);
	_objectManager->spawnObject(OBJECT_TYPE::DESK, Vector3(970, 0, 700), DIRECTION::LEFT, 6);
	_objectManager->spawnObject(OBJECT_TYPE::DESK, Vector3(1230, 0, 700), DIRECTION::LEFT, 7);



	_objectManager->spawnObject(OBJECT_TYPE::mrRudis, Vector3(1670, 0, 510), DIRECTION::LEFT, 1);
	_objectManager->spawnObject(OBJECT_TYPE::schoolBoyB, Vector3(400, 0, 400), DIRECTION::LEFT, 1);
	_objectManager->spawnObject(OBJECT_TYPE::schoolGirlB, Vector3(500, 0, 400), DIRECTION::RIGHT, 1);

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
	_objectManager->update();
	_enemyManager->update();

	CAMERA_MANAGER->setXY(CAMERA_MANAGER->convertV3ToV2(_player->getPosition()));

	return nullptr;
}

void Stage::render()
{
	// 배경이미지 그리기
	Vector2 bgCenter;
	bgCenter.x = _background->getWidth() * _bgScale * 0.5;
	bgCenter.y = _background->getHeight() * _bgScale * 0.5;
	_background->setScale(_bgScale);
	CAMERA_MANAGER->render(_background, bgCenter);

	for (int i = 0; i < _restrictLines.size(); i++)
	{
		_restrictLines[i]->render();
	}

	_objectManager->render();
	_enemyManager->render();
}

// 게임 오브젝트가 이동가능한 영역까지 이동할 수 있도록 하는 함수
void Stage::moveGameObject(GameObject* gameObject, Vector3 move)
{
	if (move.x == 0 && move.y == 0 && move.z == 0) return;

	float dir[4][2] = { {-1.0, -1.0}, {-1.0, 1.0}, {1.0, -1.0}, {1.0, 1.0} }; // 각 대각 값
	float width = gameObject->getSize().x * 0.5; // 충돌 가로 길이
	float height = gameObject->getSize().z * 0.5; // 충돌 세로 길이

	Vector3 newPos = gameObject->getPosition() + move;
	Vector3 size = gameObject->getSize();
	if (newPos.y + (size.y / 2) > 0)
	{
		newPos.y = -(size.y / 2);
	}

	Vector3 newPoses[4]; // 새로운 좌표를 기준으로 하는 대각 위치
	for (int i = 0; i < 4; i++)
	{
		newPoses[i] = Vector3(newPos.x + dir[i][0] * width, newPos.y, newPos.z + dir[i][1] * height);
	}

	// 선분과의 이동가능 비교는 x, z 비교
	for (int i = 0; i < _restrictLines.size(); i++)
	{
		_restrictLines[i]->checkCollision(newPoses, size);
	}

	// 물체와의 이동가능 비교는 x, y, z 비교, 물체를 올라탈 수도 있음
	_objectManager->collision(newPoses, gameObject);

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
