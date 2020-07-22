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

	int linePos[4][4] = { {0, 660, _background->getWidth() * _bgScale, 660},
		{_background->getWidth() * _bgScale, 770, _background->getWidth() * _bgScale - 770, 0},
	{0, 740, 740, 0},
	{0, 380, _background->getWidth() * _bgScale, 380} };
	for (int i = 0; i < 4; i++)
	{
		Vector2 lineStart;
		lineStart.x = linePos[i][0];
		lineStart.y = linePos[i][1];
		Vector2 lineEnd;
		lineEnd.x = linePos[i][2];
		lineEnd.y = linePos[i][3];
		if (i >= 1)
		{
			_linearFuncs.push_back({ LinearFunc::getLinearFuncFromPoints(lineStart, lineEnd), LINEAR_VALUE_TYPE::UP });
		}
		else
		{
			_linearFuncs.push_back({ LinearFunc::getLinearFuncFromPoints(lineStart, lineEnd), LINEAR_VALUE_TYPE::DOWN });
		}
	}

	_objectManager = new ObjectManager;
	_objectManager->init();
	_objectManager->spawnObject(OBJECT_TYPE::DESK, Vector3(720, 0, 550), DIRECTION::LEFT);

	_enemyManager = new EnemyManager;
	_enemyManager->setStage(this);
	_enemyManager->init();
}

Stage * Stage::update()
{
	_objectManager->update();
	_enemyManager->update();

	return nullptr;
}

void Stage::render()
{
	// ����̹��� �׸���
	Vector2 bgCenter;
	bgCenter.x = _background->getWidth() * _bgScale * 0.5;
	bgCenter.y = _background->getHeight() * _bgScale * 0.5;
	_background->setScale(_bgScale);
	CAMERA_MANAGER->render(_background, bgCenter);

	int linePos[4][4] = { {0, 660, _background->getWidth() * _bgScale, 660},
		{_background->getWidth() * _bgScale, 770, _background->getWidth() * _bgScale - 770, 0},
	{0, 740, 740, 0}, 
	{0, 380, _background->getWidth() * _bgScale, 380}  };
	for (int i = 0; i < 4; i++)
	{
		Vector2 lineStart;
		lineStart.x = linePos[i][0];
		lineStart.y = linePos[i][1];
		Vector2 lineEnd;
		lineEnd.x = linePos[i][2];
		lineEnd.y = linePos[i][3];
		CAMERA_MANAGER->drawLine(lineStart, lineEnd);
	}

	_objectManager->render();
	_enemyManager->render();
}

// ���� ������Ʈ�� �̵������� �������� �̵��� �� �ֵ��� �ϴ� �Լ�
void Stage::moveGameObject(GameObject & gameObject, Vector3 move)
{
	if (move.x == 0 && move.y == 0 && move.z == 0) return;

	float dir[4][2] = { {-1.0, -1.0}, {-1.0, 1.0}, {1.0, -1.0}, {1.0, 1.0} }; // �� �밢 ��
	float width = gameObject.getSize().x * 0.5; // �浹 ���� ����
	float height = gameObject.getSize().z * 0.5; // �浹 ���� ����

	Vector3 newPos = gameObject.getPosition() + move;
	Vector3 newPoses[4]; // ���ο� ��ǥ�� �������� �ϴ� �밢 ��ġ
	for (int i = 0; i < 4; i++)
	{
		newPoses[i] = Vector3(newPos.x + dir[i][0] * width, newPos.y, newPos.z + dir[i][1] * height);
	}

	// ���а��� �̵����� �񱳴� x, z ��
	for (int i = 0; i < _linearFuncs.size(); i++)
	{
		for (int j = 0; j < 4; j++) // �밢 ���鿡 ���Ͽ� ��
		{
			Vector3 checkPos = newPoses[j];
			LINEAR_VALUE_TYPE type = _linearFuncs[i].line.getValueType(checkPos.x, checkPos.z);
			if (type == _linearFuncs[i].type) // ���� �Ѿ ���
			{
				if (_linearFuncs[i].line.a != 0) // ���Ⱑ 0�� ���
				{
					checkPos.x = _linearFuncs[i].line.getX(checkPos.z); // x ��ǥ ������ z�� ��������
				}
				else
				{
					checkPos.z = _linearFuncs[i].line.getY(checkPos.x); // z ��ǥ ������ x�� ��������
				}

				// �ٲ� ��ǥ�� �������� �ٽ� �׸���
				newPos = Vector3(checkPos.x - dir[j][0] * width, newPos.y, checkPos.z - dir[j][1] * height);
				for (int k = 0; k < 4; k++)
				{
					newPoses[k] = Vector3(newPos.x + dir[k][0] * width, newPos.y, newPos.z + dir[k][1] * height);
				}
			}
		}
	}

	// ��ü���� �̵����� �񱳴� x, y, z ��, ��ü�� �ö�Ż ���� ����
	gameObject.setPosition(newPos);
}

Vector3 Stage::getPlayerPosition()
{
	return _player->getPosition();
}
