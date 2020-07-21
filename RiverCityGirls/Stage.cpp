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

	_enemyManager = new EnemyManager;
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

	Vector3 newPos = gameObject.GetPosition() + move;
	
	// ���а��� �̵����� �񱳴� x, z ��
	for (int i = 0; i < _linearFuncs.size(); i++)
	{
		LINEAR_VALUE_TYPE type = _linearFuncs[i].line.getValueType(newPos.x, newPos.z);
		if (type == _linearFuncs[i].type) // ������ �Ѿ ���
		{
			if (_linearFuncs[i].line.a != 0)
			{
				newPos.x = _linearFuncs[i].line.getX(newPos.z);
			}
			else
			{
				newPos.z = _linearFuncs[i].line.getY(newPos.x);
			}
		}

		//for (int j = 0; j < 4; j++) // �浹 ���� RECT�� �� �������� ��
		//{
		//	
		//}
	}

	// ��ü���� �̵����� �񱳴� x, y, z ��

	gameObject.SetPosition(newPos);
}
