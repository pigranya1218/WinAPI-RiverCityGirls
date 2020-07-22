#pragma once
#include "LinearFunc.h"
#include "GameObject.h"

class RestrictMoveRect
{
private:
	Vector2 _point[4]; // LT, RT, RB, LB
	LinearFunc* _lines[4]; // L T R B
	float _height;

public:
	RestrictMoveRect(Vector2 LT, Vector2 RT, Vector2 RB, Vector2 LB, float height)
	{
		_point[0] = LT;
		_point[1] = RT;
		_point[2] = RB;
		_point[3] = LB;

		_lines[0] = new LinearFunc(LB, LT); // LEFT
		_lines[1] = new LinearFunc(LT, RT); // TOP
		_lines[2] = new LinearFunc(RB, RT); // RIGHT
		_lines[3] = new LinearFunc(LB, RB); // BOTTOM

		_height = -height;
	}

	RestrictMoveRect(Vector3 position, Vector3 size)
	{
		int linePos[2][4] = { {position.x - (size.x / 2) + (size.z / 2) , position.z - (size.z / 2), position.x + (size.x / 2) + (size.z / 2), position.z - (size.z / 2)}, // ¿≠ ¡Ÿ 
						{position.x - (size.x / 2) - (size.z / 2), position.z + (size.z / 2), position.x + (size.x / 2) - (size.z / 2), position.z + (size.z / 2)}, }; // æ∆∑ß ¡Ÿ

		RestrictMoveRect(Vector2(linePos[0][0], linePos[0][1]),		// LT
			Vector2(linePos[0][2], linePos[0][3]),		// RT
			Vector2(linePos[1][2], linePos[1][3]),		// RB
			Vector2(linePos[1][0], linePos[1][1]),
			-size.y);		// LB
	}

	~RestrictMoveRect()
	{
		for (int i = 0; i < 4; i++)
		{
			delete _lines[i];
		}
	}

	void checkCollision(Vector3* poses, GameObject* gameObject);

	// FOR DEBUG
	void render();
};

