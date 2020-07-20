#include "stdafx.h"
#include "Stage.h"
#include "StageManager.h"

void Stage::render()
{
	// 배경이미지 그리기
	Vector2 center;
	center.x = _background->getWidth() / 2;
	center.y = _background->getHeight() / 2;
	CAMERA_MANAGER->render(_background, center);
}

// 게임 오브젝트가 이동가능한 영역까지 이동할 수 있도록 하는 함수
void Stage::moveGameObject(GameObject & gameObject, Vector3 move)
{
	Vector3 newPos = gameObject.GetPosition() + move;
	
	// 선분과의 이동가능 비교는 x, z 비교
	for (int i = 0; i < _linearFuncs.size(); i++)
	{
		LINEAR_VALUE_TYPE type = _linearFuncs[i].line.getValueType(newPos.x, newPos.z);
		if (type == _linearFuncs[i].type)
		{
			newPos.x = _linearFuncs[i].line.getX(newPos.z);
		}
	}

	// 물체와의 이동가능 비교는 x, y, z 비교

	gameObject.SetPosition(newPos);
}
