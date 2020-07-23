#include "stdafx.h"
#include "MiddleStage.h"
#include "StageManager.h"
#include "EnemyManager.h"

void MiddleStage::init(Image * background, float bgScale)
{
	Stage::init(background, bgScale);

	int linePos[10][4] = { {0, 835, _background->getWidth() * _bgScale, 835}, // ��
							{0, 490, _background->getWidth() * _bgScale, 490}, // �� ù��°          
						{920, 490, 921, 491}, // �� �ι�°
						{0, 545, 1, 545}, // �� ����°
						{1640, 545, 1641, 544}, // �� �׹�°
						{1745, 440, 1741, 440}, // �� �ټ���°
						{_background->getWidth() * _bgScale - 1, 10, _background->getWidth() * _bgScale - 1, 100}, // ������ ������
						{1, 10, 1, 100}, // ���� ������
						{_background->getWidth() * _bgScale, 795, _background->getWidth() * _bgScale - 795, 0}, // ��
						{0, 750, 750, 0} }; // ��
	LINEAR_VALUE_TYPE lineTypes[10] = { LINEAR_VALUE_TYPE::DOWN,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::RIGHT,
										LINEAR_VALUE_TYPE::LEFT,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::UP };
	float lineRange[10][4] = { {0, _background->getWidth() * _bgScale} , // ��
								{260, 920}, // �� ù��°
								{920, 975}, // �� �ι�°
								{975, 1640}, // �� ����°
								{1640, 1745}, // �� �׹�°
								{1745, 2505}, // �� �ټ���°
								{795, 835}, // ������ ������
								{750, 835}, // ���� ������
								{2505, _background->getWidth() * _bgScale}, // ��
								{0, 260} }; // ��
	for (int i = 0; i < 10; i++)
	{
		LinearFunc line = LinearFunc::getLinearFuncFromPoints(Vector2(linePos[i][0], linePos[i][1]), Vector2(linePos[i][2], linePos[i][3]));
		_restrictLines.push_back(new RestrictMoveLine(line, lineTypes[i], lineRange[i][0], lineRange[i][1]));
	}

	//Object ��ġ


	DOOR_STATE doorStates[3] = {DOOR_STATE::UNLOCK, DOOR_STATE::SHOP, DOOR_STATE::LOCK};
	Vector3 doorPoses[3] = {Vector3(80, -200, 700),
							Vector3(1165, -200, 560) ,
							Vector3(2710, -200, 700) };
	for (int i = 0; i < 3; i++)
	{
		tagDoorInfo door;
		door.doorState = doorStates[i];
		door.pos = doorPoses[i];
		_doorInfos.push_back(door);
	}

	string destNames[3] = {"START_STAGE", "SHOP", "BOSS_STATE"};
	Vector3 destPoses[3] = {Vector3(1250, -(_player->getSize().y * 0.5), 400),
							Vector3() ,
							Vector3(100, -(_player->getSize().y * 0.5), 700) };
	for(int i = 0 ; i < 3 ; i++)
	{ 
		tagDoorDestination doorDest;
		doorDest.destName = destNames[i];
		doorDest.destPos = destPoses[i];
		_doorDestination.push_back(doorDest);
	}
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
			if (KEY_MANAGER->isOnceKeyDown('Z'))
			{
				switch (_doorInfos[i].doorState)
				{
				case DOOR_STATE::SHOP:
				{

				}
				break;
				case DOOR_STATE::UNLOCK:
				{
					_player->setPosition(_doorDestination[i].destPos);
					return _stageManager->getStage(_doorDestination[i].destName);
				}
				}
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