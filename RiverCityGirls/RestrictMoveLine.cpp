#include "stdafx.h"
#include "RestrictMoveLine.h"

void RestrictMoveLine::checkCollision(Vector3 * poses, Vector3 size)
{
	float dir[4][2] = { {-1.0, -1.0}, {-1.0, 1.0}, {1.0, -1.0}, {1.0, 1.0} }; // �� �밢 ��
	float width = size.x / 2;
	float height = size.z / 2;

	for (int i = 0; i < 4; i++) // 4 �������� ���� �˻�
	{
		Vector3 checkPos = poses[i];
		if (_startX > poses[i].x || _endX < poses[i].x) continue; // �˻����� �ʾƵ� �Ǵ� ��ǥ

		LINEAR_VALUE_TYPE posType = _line.getValueType(checkPos.x, checkPos.z);
		if (posType == _type) // ���� �Ѿ ���
		{
			if (_line.a != 0) // ���Ⱑ 0�� �ƴ� ���
			{
				checkPos.x = _line.getX(checkPos.z); // x ��ǥ ������ z�� ��������
			}
			else
			{
				checkPos.z = _line.getY(checkPos.x); // z ��ǥ ������ x�� ��������
			}

			// �ٲ� ��ǥ�� �������� �ٽ� �׸���
			Vector3 newPos = Vector3(checkPos.x - dir[i][0] * width, checkPos.y, checkPos.z - dir[i][1] * height);
			for (int k = 0; k < 4; k++)
			{
				poses[k] = Vector3(newPos.x + dir[k][0] * width, checkPos.y, newPos.z + dir[k][1] * height);
			}
		}
	}
}

void RestrictMoveLine::render()
{
	Vector2 startPoint = Vector2(_startX, _line.getY(_startX));
	Vector2 endPoint = Vector2(_endX, _line.getY(_endX));
	CAMERA_MANAGER->drawLine(startPoint, endPoint);
}
