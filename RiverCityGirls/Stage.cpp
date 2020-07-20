#include "stdafx.h"
#include "Stage.h"
#include "StageManager.h"

void Stage::render()
{
	// ����̹��� �׸���
	Vector2 center;
	center.x = _background->getWidth() / 2;
	center.y = _background->getHeight() / 2;
	CAMERA_MANAGER->render(_background, center);
}

// ���� ������Ʈ�� �̵������� �������� �̵��� �� �ֵ��� �ϴ� �Լ�
void Stage::moveGameObject(GameObject & gameObject, Vector3 move)
{
	Vector3 newPos = gameObject.GetPosition() + move;
	
	// ���а��� �̵����� �񱳴� x, z ��
	for (int i = 0; i < _linearFuncs.size(); i++)
	{
		LINEAR_VALUE_TYPE type = _linearFuncs[i].line.getValueType(newPos.x, newPos.z);
		if (type == _linearFuncs[i].type)
		{
			newPos.x = _linearFuncs[i].line.getX(newPos.z);
		}
	}

	// ��ü���� �̵����� �񱳴� x, y, z ��

	gameObject.SetPosition(newPos);
}
