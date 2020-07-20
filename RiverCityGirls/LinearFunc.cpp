#include "stdafx.h"
#include "LinearFunc.h"

LINEAR_VALUE_TYPE LinearFunc::getValueType(float x, float y)
{
	float result = y - (a * x + b);
	if (FLOAT_EQUAL(result, 0))
	{
		return LINEAR_VALUE_TYPE::ON;
	}
	else if (result > 0)
	{
		return LINEAR_VALUE_TYPE::UP;
	}
	else
	{
		return LINEAR_VALUE_TYPE::DOWN;
	}
}
