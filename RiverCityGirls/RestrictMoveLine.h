#pragma once
#include "LinearFunc.h"


class RestrictMoveLine
{
private:
	LinearFunc _line; // ����
	LINEAR_VALUE_TYPE _type; // �� ���� ��� ���������� �� ���ΰ�?
	float _startX; // ������ �� X�� ���� ��ǥ
	float _endX; // ������ �� X�� ������ ��ǥ range : [_startX, _endX]

public:
	RestrictMoveLine(LinearFunc line, LINEAR_VALUE_TYPE type, float startX, float endX)
		: _line(line), _type(type), _startX(startX), _endX(endX)
	{
	}

	void checkCollision(Vector3* poses, Vector3 size);

	// FOR DEBUG
	void render(); 
};

