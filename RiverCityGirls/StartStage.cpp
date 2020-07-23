#include "stdafx.h"
#include "StartStage.h"
#include "MiddleStage.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#include "StageManager.h"

void StartStage::init(Image * background, float bgScale)
{
	Stage::init(background, bgScale);

	int linePos[4][4] = { {0, 670, _background->getWidth() * _bgScale, 670}, // ��
							{0, 380, _background->getWidth() * _bgScale, 380}, // ��
						{_background->getWidth() * _bgScale, 770, _background->getWidth() * _bgScale - 770, 0}, // ��
						{0, 740, 740, 0} }; // ��
	LINEAR_VALUE_TYPE lineTypes[4] = { LINEAR_VALUE_TYPE::DOWN,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::UP };
	float lineRange[4][4] = { {70, _background->getWidth() * _bgScale - 100} , // ��
								{360, 1625}, // ��
								{1625, _background->getWidth() * _bgScale - 100}, // ��
								{70, 360} }; // ��
	for (int i = 0; i < 4; i++)
	{
		LinearFunc line = LinearFunc::getLinearFuncFromPoints(Vector2(linePos[i][0], linePos[i][1]), Vector2(linePos[i][2], linePos[i][3]));
		_restrictLines.push_back(new RestrictMoveLine(line, lineTypes[i], lineRange[i][0], lineRange[i][1]));
	}
	
	_objectManager->spawnObject(OBJECT_TYPE::DESK, OBJECT_STATE::IDLE01, Vector3(1200, 0, 495), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::DESK, OBJECT_STATE::IDLE01, Vector3(940, 0, 495), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::DESK, OBJECT_STATE::IDLE01, Vector3(680, 0, 495), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::DESK, OBJECT_STATE::IDLE01, Vector3(430, 0, 495), DIRECTION::LEFT);

	//Object ��ġ
	//_objectManager->spawnObject(OBJECT_TYPE::DESK, OBJECT_STATE::IDLE01, Vector3(710, 0, 510), DIRECTION::LEFT);
	//_objectManager->spawnObject(OBJECT_TYPE::DESK, OBJECT_STATE::IDLE01, Vector3(990, 0, 510), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::mrRudis, OBJECT_STATE::IDLE01, Vector3(1670, 0, 510), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::schoolBoyB, OBJECT_STATE::IDLE01, Vector3(400, 0, 400), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::schoolGirlB, OBJECT_STATE::IDLE01, Vector3(550, 0, 400), DIRECTION::RIGHT);

	_doorInfos.push_back({DOOR_STATE::UNLOCK, Vector3(500, 0, 500)});
	_stageManager->setDoorInfo(_doorInfos);
}

void StartStage::enter()
{
}

void StartStage::exit()
{
	Stage::exit();
}

Stage * StartStage::update()
{
	for (int i = 0; i < _doorInfos.size(); i++)
	{
		if (_doorInfos[i].door == DOOR_STATE::LOCK) continue;
		if (Vector3::distance(_doorInfos[i].pos, _player->getPosition()) < 100)
		{
			if (KEY_MANAGER->isStayKeyDown('Z'))
			{
				_player->setPosition(Vector3(400, -(_player->getSize().y * 0.5), 400));
				return _stageManager->getStage("MIDDLE_STAGE");
			}
		}
	}

	_objectManager->update();
	_enemyManager->update();
	CAMERA_MANAGER->setXY(CAMERA_MANAGER->convertV3ToV2(_player->getPosition()));

	return nullptr;
}

void StartStage::render()
{
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
