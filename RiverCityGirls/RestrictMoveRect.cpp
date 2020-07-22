#include "stdafx.h"
#include "RestrictMoveRect.h"

void RestrictMoveRect::checkCollision(Vector3 * poses, Vector3 size)
{
	float width = size.x / 2;
	float height = size.z / 2;

	for (int i = 0; i < 4; i++) // �������� ����纯�� ������ ���Դ��� �˻��ϱ�
	{
		Vector3 checkPos = poses[i];

		if ((_lines[0]->getValueType(checkPos.x, checkPos.z) == LINEAR_VALUE_TYPE::DOWN) &&
			(_lines[1]->getValueType(checkPos.x, checkPos.z) == LINEAR_VALUE_TYPE::DOWN) &&
			(_lines[2]->getValueType(checkPos.x, checkPos.z) == LINEAR_VALUE_TYPE::UP) &&
			(_lines[3]->getValueType(checkPos.x, checkPos.z) == LINEAR_VALUE_TYPE::UP))
		{
			// ��ǥ�� �����¿� �� ���� ����� ��ǥ�� �����Ѵ�.








			//	// �ٲ� ��ǥ�� �������� �ٽ� �׸���
			//	Vector3 newPos = Vector3(checkPos.x - dir[i][0] * width, checkPos.y, checkPos.z - dir[i][1] * height);
			//	for (int k = 0; k < 4; k++)
			//	{
			//		poses[k] = Vector3(newPos.x + dir[k][0] * width, checkPos.y, newPos.z + dir[k][1] * height);
			//	}
		}
	}
}

void RestrictMoveRect::render()
{
	for (int i = 0; i < 4; i++)
	{
		CAMERA_MANAGER->drawLine(_point[i], _point[(i + 1) % 4]);
	}
}
