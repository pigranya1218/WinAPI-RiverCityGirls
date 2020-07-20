#include "stdafx.h"
#include "Stage.h"
#include "StageManager.h"

void Stage::init(Image * background, float bgScale)
{
	_background = background;
	_bgScale = bgScale;
	float maxWidth = _background->getWidth() * _bgScale;
	float maxHeight = _background->getHeight() * _bgScale; 
	//CAMERA_MANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 1000, 1000);
	CAMERA_MANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, maxWidth - WINSIZEX, maxHeight - WINSIZEY);

	int linePos[3][4] = { {0, 740, 740, 0}, {0, 380, _background->getWidth() * _bgScale, 380}, {_background->getWidth() * _bgScale, 770, _background->getWidth() * _bgScale - 770, 0} };
	for (int i = 0; i < 3; i++)
	{
		Vector2 lineStart;
		lineStart.x = linePos[i][0];
		lineStart.y = linePos[i][1];
		Vector2 lineEnd;
		lineEnd.x = linePos[i][2];
		lineEnd.y = linePos[i][3];
		_linearFuncs.push_back({ LinearFunc::getLinearFuncFromPoints(lineStart, lineEnd), LINEAR_VALUE_TYPE::UP });
	}
}

void Stage::render()
{
	// ����̹��� �׸���
	Vector2 bgCenter;
	bgCenter.x = _background->getWidth() * _bgScale * 0.5;
	bgCenter.y = _background->getHeight() * _bgScale * 0.5;
	_background->setScale(_bgScale);
	CAMERA_MANAGER->render(_background, bgCenter);

	int linePos[3][4] = { {0, 740, 740, 0}, {_background->getWidth() * _bgScale, 770, _background->getWidth() * _bgScale - 770, 0}, {0, 380, _background->getWidth() * _bgScale, 380} };
	for (int i = 0; i < 3; i++)
	{
		Vector2 lineStart;
		lineStart.x = linePos[i][0];
		lineStart.y = linePos[i][1];
		Vector2 lineEnd;
		lineEnd.x = linePos[i][2];
		lineEnd.y = linePos[i][3];
		CAMERA_MANAGER->drawLine(lineStart, lineEnd);
	}

	
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
			newPos.x = _linearFuncs[i].line.getX(newPos.z);
		}

		//for (int j = 0; j < 4; j++) // �浹 ���� RECT�� �� �������� ��
		//{
		//	
		//}
	}

	// ��ü���� �̵����� �񱳴� x, y, z ��

	gameObject.SetPosition(newPos);
}
