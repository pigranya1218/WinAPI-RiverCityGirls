#include "stdafx.h"
#include "LinearFunc.h"

LinearFunc::LinearFunc(Vector2 start, Vector2 end)
{
	a = (start.y - end.y) / (start.x - end.x); // x 변화량에 대한 y 변화량 비율
	b = start.y - (start.x * a); // y 절편
}

LINEAR_VALUE_TYPE LinearFunc::getValueType(float x, float y)
{
	float result = y - (a * x + b);
	if (FLOAT_EQUAL(result, 0))
	{
		return LINEAR_VALUE_TYPE::ON;
	}
	else if (result < 0)
	{
		return LINEAR_VALUE_TYPE::UP;
	}
	else
	{
		return LINEAR_VALUE_TYPE::DOWN;
	}
}

LinearFunc LinearFunc::getLinearFuncFromPoints(Vector2 start, Vector2 end)
{
	LinearFunc newFunc;
	newFunc.a = (start.y - end.y) / (start.x - end.x); // x 변화량에 대한 y 변화량 비율
	newFunc.b = start.y - (start.x * newFunc.a); // y 절편
	return newFunc;
}
