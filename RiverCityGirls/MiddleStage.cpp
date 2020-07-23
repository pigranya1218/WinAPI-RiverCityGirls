#include "stdafx.h"
#include "MiddleStage.h"
#include "StageManager.h"
#include "EnemyManager.h"

void MiddleStage::init(Image * background, float bgScale)
{
	Stage::init(background, bgScale);

	int linePos[4][4] = { {0, 670, _background->getWidth() * _bgScale, 670}, // ÇÏ
							{0, 380, _background->getWidth() * _bgScale, 380}, // »ó                                                                                                                                                                              
						{_background->getWidth() * _bgScale, 770, _background->getWidth() * _bgScale - 770, 0}, // ¿ì
						{0, 740, 740, 0} }; // ÁÂ
	LINEAR_VALUE_TYPE lineTypes[4] = { LINEAR_VALUE_TYPE::DOWN,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::UP };
	float lineRange[4][4] = { {70, _background->getWidth() * _bgScale - 100} , // ÇÏ
								{360, 1625}, // »ó
								{1625, _background->getWidth() * _bgScale - 100}, // ÁÂ
								{70, 360} }; // ¿ì
	for (int i = 0; i < 4; i++)
	{
		LinearFunc line = LinearFunc::getLinearFuncFromPoints(Vector2(linePos[i][0], linePos[i][1]), Vector2(linePos[i][2], linePos[i][3]));
		_restrictLines.push_back(new RestrictMoveLine(line, lineTypes[i], lineRange[i][0], lineRange[i][1]));
	}

	//Object ¹èÄ¡
	//_objectManager->spawnObject(OBJECT_TYPE::DESK, OBJECT_STATE::IDLE01, Vector3(710, 0, 510), DIRECTION::LEFT);
	//_objectManager->spawnObject(OBJECT_TYPE::DESK, OBJECT_STATE::IDLE01, Vector3(990, 0, 510), DIRECTION::LEFT);

	tagDoorInfo door;
	door.doorState = DOOR_STATE::UNLOCK;
	door.pos = Vector3(1430, -200, 420);
	_doorInfos.push_back(door);
}

void MiddleStage::enter()
{
	Stage::enter();
}

void MiddleStage::exit()
{
	Stage::exit();
}

Stage * MiddleStage::update()
{
	for (int i = 0; i < _doorInfos.size(); i++)
	{
		if (_doorInfos[i].doorState == DOOR_STATE::LOCK) continue;
		if (Vector3::distance(_doorInfos[i].pos, _player->getPosition()) < 150)
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

void MiddleStage::render()
{
	Vector2 bgCenter;
	bgCenter.x = _background->getWidth() * _bgScale * 0.5;
	bgCenter.y = _background->getHeight() * _bgScale * 0.5;
	_background->setScale(_bgScale);
	CAMERA_MANAGER->render(_background, bgCenter);

	if (DEBUG_MANAGER->isDebugMode(DEBUG_TYPE::STAGE))
	{
		for (int i = 0; i < _restrictLines.size(); i++)
		{
			_restrictLines[i]->render();
		}
	}


	_objectManager->render();
	_enemyManager->render();
}
