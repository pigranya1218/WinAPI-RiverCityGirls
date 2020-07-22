#pragma once
#include "LinearFunc.h"

class RestrictMoveRect
{
private:
	Vector2 _point[4]; // LT, RT, RB, LB
	LinearFunc* _lines[4]; // L T R B

public:
	RestrictMoveRect(Vector2 LT, Vector2 RT, Vector2 RB, Vector2 LB)
	{
		_point[0] = LT;
		_point[1] = RT;
		_point[2] = RB;
		_point[3] = LB;

		_lines[0] = new LinearFunc(LB, LT); // LEFT
		_lines[1] = new LinearFunc(LT, RT); // TOP
		_lines[2] = new LinearFunc(RB, RT); // RIGHT
		_lines[3] = new LinearFunc(LB, RB); // BOTTOM
	}

	~RestrictMoveRect()
	{
		for (int i = 0; i < 4; i++)
		{
			delete _lines[i];
		}
	}

	void checkCollision(Vector3* poses, Vector3 size);

	// FOR DEBUG
	void render();
};

