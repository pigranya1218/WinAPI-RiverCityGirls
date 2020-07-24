#include "stdafx.h"
#include "RestrictMoveRect.h"

void RestrictMoveRect::checkCollision(Vector3 * poses, GameObject* gameObject)
{
	float dir[4][2] = { {-1.0, -1.0}, {-1.0, 1.0}, {1.0, -1.0}, {1.0, 1.0} }; // �� �밢 ��
	Vector3 size = gameObject->getSize();
	float widthX = size.x / 2;
	float widthZ = size.z / 2;
	float height = size.y / 2;
	float lastBottom = gameObject->getPosition().y + height;
	float gameObjectBottom = poses[0].y + height;

	// ���� ���ӿ�����Ʈ�� �ٴ��� �浹���� ���̺��� �� ���ٸ� �˻����� �ʴ´�.
	if (gameObjectBottom < _height)
	{
		return;
	}

	if (_type == RECT_TYPE::MIDDLE) // ���簢�� ��Ʈ �浹�� ���
	{
		
		for (int i = 0; i < 4; i++)
		{
			if (_lines[0].getValueType(poses[i].x, poses[i].z) == LINEAR_VALUE_TYPE::RIGHT &&
				_lines[1].getValueType(poses[i].x, poses[i].z) == LINEAR_VALUE_TYPE::DOWN &&
				_lines[2].getValueType(poses[i].x, poses[i].z) == LINEAR_VALUE_TYPE::LEFT &&
				_lines[3].getValueType(poses[i].x, poses[i].z) == LINEAR_VALUE_TYPE::UP) // �ȿ� ���� ���
			{
				if (lastBottom <= _height && _height <= gameObjectBottom) // �������� ��
				{
					for (int i = 0; i < 4; i++)
					{
						poses[i].y = _height - height;
					}
					return;
				}
				else
				{
					int checkIndex[4][2] = { {2, 3}, {2, 1}, {0, 3}, {0, 1} }; // ������ ������ ���� �˻��ؾ��ϴ� ����
					float minX = _lines[checkIndex[i][0]].b;
					float minZ = poses[i].z;
					float minDistance = TTYONE_UTIL::getDistance(poses[i].x, poses[i].z, minX, minZ);

					float x = poses[i].x;
					float z = _lines[checkIndex[i][1]].getY(x);
					float distance = TTYONE_UTIL::getDistance(poses[i].x, poses[i].z, x, z);

					if (minDistance > distance)
					{
						minX = x;
						minZ = z;
					}
					Vector3 newPos = Vector3(minX - dir[i][0] * widthX, poses[i].y, minZ - dir[i][1] * widthZ);
					for (int k = 0; k < 4; k++)
					{
						poses[k] = Vector3(newPos.x + dir[k][0] * widthX, newPos.y, newPos.z + dir[k][1] * widthZ);
					}
				}
			}
		}

	}
	else // ����纯���� ���簢�� ��Ʈ �浹�� ���
	{
		Vector3 checkMid[2]; // 0 : ������, 1 : �Ʒ�����
		for (int i = 0; i < 2; i++)
		{
			checkMid[i] = (poses[i] + poses[i + 2]) * 0.5;
		}
		// 1. �� �Ʒ� ������ ����纯�� ������ ���Դ��� �˻��ϱ�
		if ((_lines[3].getValueType(checkMid[0].x, checkMid[0].z) == LINEAR_VALUE_TYPE::UP) &&
			(_lines[3].getValueType(checkMid[1].x, checkMid[1].z) == LINEAR_VALUE_TYPE::DOWN) &&
			_point[3].x < checkMid[0].x && checkMid[0].x < _point[2].x) // �� ������ ����纯�� �Ʒ����� �ε�������
		{
			if (lastBottom <= _height && _height <= gameObjectBottom) // �������� ��
			{
				for (int i = 0; i < 4; i++)
				{
					poses[i].y = _height - height;
				}
				return;
			}
			else
			{
				int checkIndex[2][2] = { {2, 3}, {0, 1} }; // ������ ������ ���� �˻��ؾ��ϴ� ����
				checkMid[0].z = _lines[3].getY(checkMid[0].x);
				Vector3 newPos = Vector3(checkMid[0].x, checkMid[0].y, checkMid[0].z + widthZ);
				for (int k = 0; k < 4; k++)
				{
					poses[k] = Vector3(newPos.x + dir[k][0] * widthX, newPos.y, newPos.z + dir[k][1] * widthZ);
				}
			}
		}
		if ((_lines[1].getValueType(checkMid[0].x, checkMid[0].z) == LINEAR_VALUE_TYPE::UP) &&
			(_lines[1].getValueType(checkMid[1].x, checkMid[1].z) == LINEAR_VALUE_TYPE::DOWN) &&
			_point[0].x < checkMid[1].x && checkMid[1].x < _point[1].x) // �Ʒ� ������ ����纯�� ������ �ε�������
		{
			if (lastBottom <= _height && _height <= gameObjectBottom) // �������� ��
			{
				for (int i = 0; i < 4; i++)
				{
					poses[i].y = _height - height;
				}
				return;
			}
			{
				checkMid[1].z = _lines[1].getY(checkMid[1].x);
				Vector3 newPos = Vector3(checkMid[1].x, checkMid[1].y, checkMid[1].z - widthZ);
				for (int k = 0; k < 4; k++)
				{
					poses[k] = Vector3(newPos.x + dir[k][0] * widthX, newPos.y, newPos.z + dir[k][1] * widthZ);
				}
			}
		}


		if (_type == RECT_TYPE::RIGHT) // ���������� ��� ����纯��
		{
			// 2. �浹���� ��Ʈ �������� ����纯�� ������ ���Դ��� �˻��ϱ�
			int checkIndex[2][2] = { {2, 3}, {0, 1} }; // ������ ������ ���� �˻��ؾ��ϴ� ����
			for (int i = 0; i < 4; i++)
			{
				Vector3 checkPos = poses[i];

				if ((_lines[0].getValueType(checkPos.x, checkPos.z) == LINEAR_VALUE_TYPE::DOWN) &&
					(_lines[1].getValueType(checkPos.x, checkPos.z) == LINEAR_VALUE_TYPE::DOWN) &&
					(_lines[2].getValueType(checkPos.x, checkPos.z) == LINEAR_VALUE_TYPE::UP) &&
					(_lines[3].getValueType(checkPos.x, checkPos.z) == LINEAR_VALUE_TYPE::UP))
				{
					if (lastBottom <= _height && _height <= gameObjectBottom) // �������� ��
					{
						for (int i = 0; i < 4; i++)
						{
							poses[i].y = _height - height;
						}
						return;
					}
					else
					{
						// �� �������̸� �Ʒ��� ������, �Ʒ��������̸� ���� �ø���.
						float minZ = checkPos.z;
						float minX = _lines[checkIndex[i % 2][0]].getX(minZ);
						float minDistance = TTYONE_UTIL::getDistance(checkPos.x, checkPos.z, minX, minZ);

						float x = checkPos.x;
						float z = _lines[checkIndex[i % 2][1]].getY(x);
						float distance = TTYONE_UTIL::getDistance(checkPos.x, checkPos.z, x, z);

						if (distance < minDistance)
						{
							minDistance = distance;
							minX = x;
							minZ = z;
						}

						// �ٲ� ��ǥ�� �������� �ٽ� �׸���
						Vector3 newPos = Vector3(minX - dir[i][0] * widthX, checkPos.y, minZ - dir[i][1] * widthZ);
						for (int k = 0; k < 4; k++)
						{
							poses[k] = Vector3(newPos.x + dir[k][0] * widthX, newPos.y, newPos.z + dir[k][1] * widthZ);
						}
					}
				}
			}

			// 3. ����纯���� Ƣ��� �������� �浹���� ��Ʈ �ȿ� ������ ��
			// 3 - 1. ������ Ƣ��� �𼭸��� ������ ��
			if (poses[0].x < _point[1].x && _point[1].x < poses[2].x &&
				poses[0].z < _point[1].y && _point[1].y < poses[1].z)
			{
				if (lastBottom <= _height && _height <= gameObjectBottom) // �������� ��
				{
					for (int i = 0; i < 4; i++)
					{
						poses[i].y = _height - height;
					}
					return;
				}
				else
				{
					poses[0].x = _point[1].x;
					// �ٲ� ��ǥ�� �������� �ٽ� �׸���
					Vector3 newPos = Vector3(poses[0].x - dir[0][0] * widthX, poses[0].y, poses[0].z - dir[0][1] * widthZ);
					for (int k = 0; k < 4; k++)
					{
						poses[k] = Vector3(newPos.x + dir[k][0] * widthX, newPos.y, newPos.z + dir[k][1] * widthZ);
					}
				}
			}
			// 3 - 2. ���� Ƣ��� �𼭸��� ������ ��
			if (poses[0].x < _point[3].x && _point[3].x < poses[2].x &&
				poses[0].z < _point[3].y && _point[3].y < poses[1].z)
			{
				if (lastBottom <= _height && _height <= gameObjectBottom) // �������� ��
				{
					for (int i = 0; i < 4; i++)
					{
						poses[i].y = _height - height;
					}
					return;
				}
				{
					poses[2].x = _point[3].x;
					// �ٲ� ��ǥ�� �������� �ٽ� �׸���
					Vector3 newPos = Vector3(poses[2].x - dir[2][0] * widthX, poses[2].y, poses[2].z - dir[2][1] * widthZ);
					for (int k = 0; k < 4; k++)
					{
						poses[k] = Vector3(newPos.x + dir[k][0] * widthX, newPos.y, newPos.z + dir[k][1] * widthZ);
					}
				}
			}
		}
		else // �������� ��� ����纯��
		{
			// 2. �浹���� ��Ʈ �������� ����纯�� ������ ���Դ��� �˻��ϱ�
			int checkIndex[2][2] = { {0, 3}, {2, 1} }; // ������ ������ ���� �˻��ؾ��ϴ� ����

			for (int i = 0; i < 4; i++)
			{
				Vector3 checkPos = poses[i];

				if ((_lines[0].getValueType(checkPos.x, checkPos.z) == LINEAR_VALUE_TYPE::UP) &&
					(_lines[1].getValueType(checkPos.x, checkPos.z) == LINEAR_VALUE_TYPE::DOWN) &&
					(_lines[2].getValueType(checkPos.x, checkPos.z) == LINEAR_VALUE_TYPE::DOWN) &&
					(_lines[3].getValueType(checkPos.x, checkPos.z) == LINEAR_VALUE_TYPE::UP))
				{
					if (lastBottom <= _height && _height <= gameObjectBottom) // �������� ��
					{
						for (int i = 0; i < 4; i++)
						{
							poses[i].y = _height - height;
						}
						return;
					}
					else
					{
						// �� �������̸� �Ʒ��� ������, �Ʒ��������̸� ���� �ø���.
						float minZ = checkPos.z;
						float minX = _lines[checkIndex[i % 2][0]].getX(minZ);
						float minDistance = TTYONE_UTIL::getDistance(checkPos.x, checkPos.z, minX, minZ);

						float x = checkPos.x;
						float z = _lines[checkIndex[i % 2][1]].getY(x);
						float distance = TTYONE_UTIL::getDistance(checkPos.x, checkPos.z, x, z);

						if (distance < minDistance)
						{
							minDistance = distance;
							minX = x;
							minZ = z;
						}

						// �ٲ� ��ǥ�� �������� �ٽ� �׸���
						Vector3 newPos = Vector3(minX - dir[i][0] * widthX, checkPos.y, minZ - dir[i][1] * widthZ);
						for (int k = 0; k < 4; k++)
						{
							poses[k] = Vector3(newPos.x + dir[k][0] * widthX, newPos.y, newPos.z + dir[k][1] * widthZ);
						}
					}
				}
			}

			// 3. ����纯���� Ƣ��� �������� �浹���� ��Ʈ �ȿ� ������ ��
			// 3 - 1. ������ Ƣ��� �𼭸��� ������ ��
			if (poses[0].x < _point[2].x && _point[2].x < poses[2].x &&
				poses[0].z < _point[2].y && _point[2].y < poses[1].z)
			{
				if (lastBottom <= _height && _height <= gameObjectBottom) // �������� ��
				{
					for (int i = 0; i < 4; i++)
					{
						poses[i].y = _height - height;
					}
					return;
				}
				else
				{
					poses[0].x = _point[2].x;
					// �ٲ� ��ǥ�� �������� �ٽ� �׸���
					Vector3 newPos = Vector3(poses[0].x - dir[0][0] * widthX, poses[0].y, poses[0].z - dir[0][1] * widthZ);
					for (int k = 0; k < 4; k++)
					{
						poses[k] = Vector3(newPos.x + dir[k][0] * widthX, newPos.y, newPos.z + dir[k][1] * widthZ);
					}
				}
			}
			// 3 - 2. ���� Ƣ��� �𼭸��� ������ ��
			if (poses[0].x < _point[0].x && _point[0].x < poses[2].x &&
				poses[0].z < _point[0].y && _point[0].y < poses[1].z)
			{
				if (lastBottom <= _height && _height <= gameObjectBottom) // �������� ��
				{
					for (int i = 0; i < 4; i++)
					{
						poses[i].y = _height - height;
					}
					return;
				}
				{
					poses[2].x = _point[0].x;
					// �ٲ� ��ǥ�� �������� �ٽ� �׸���
					Vector3 newPos = Vector3(poses[2].x - dir[2][0] * widthX, poses[2].y, poses[2].z - dir[2][1] * widthZ);
					for (int k = 0; k < 4; k++)
					{
						poses[k] = Vector3(newPos.x + dir[k][0] * widthX, newPos.y, newPos.z + dir[k][1] * widthZ);
					}
				}
			}
		}
	}

	
}

void RestrictMoveRect::render()
{
	for (int i = 0; i < 4; i++)
	{
		CAMERA_MANAGER->drawLine(_point[i], _point[(i + 1) % 4]);
		Vector2 upPointS = _point[i];
		upPointS.y += _height;
		Vector2 upPointE = _point[(i + 1) % 4];
		upPointE.y += _height;
		CAMERA_MANAGER->drawLine(upPointS, upPointE);
		CAMERA_MANAGER->drawLine(_point[i], upPointS);
	}

}
