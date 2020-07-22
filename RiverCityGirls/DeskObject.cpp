#include "stdafx.h"
#include "DeskObject.h"

DeskObject::DeskObject(Vector3 position, DIRECTION direction)
{
	_direction = direction;
	_size = Vector3(150, 150, 100);
	_position = Vector3(position.x, -(_size.y / 2), position.z);

	_img = IMAGE_MANAGER->findImage("OBJECT_DESK");


	int linePos[4][4] = { {0, 0, 0, 0}, // ╩С
						{0, 0, 0, 0}, // го
						{0, 0, 0, 0},  // аб
						{0, 0, 0, 0} }; // ©Л
	LINEAR_VALUE_TYPE lineTypes[4] = { LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::DOWN,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::UP };
	float lineRangeX[4][2] = { {0, 0}, // ╩С
								{0, 0}, // го
								{0, 0}, // аб
								{0, 0}, }; // ©Л
	for (int i = 0; i < 4; i++)
	{
		LinearFunc line = LinearFunc::getLinearFuncFromPoints(Vector2(linePos[i][0], linePos[i][1]), Vector2(linePos[i][2], linePos[i][3]));
		_restrictLines.push_back(new RestrictMoveLine(line, lineTypes[i], lineRangeX[i][0], lineRangeX[i][1]));
	}
}


void DeskObject::update()
{

}

void DeskObject::release()
{
	for (int i = 0; i < _restrictLines.size(); i++)
	{
		delete _restrictLines[i];
	}
	_restrictLines.clear();
}

void DeskObject::render()
{
	_img->setScale(3);
	CAMERA_MANAGER->renderZ(_img, _position, _size, false);
	
	for (int i = 0; i < _restrictLines.size(); i++)
	{
		_restrictLines[i]->render();
	}
}

void DeskObject::collision(Vector3 * pos, Vector3 size)
{

}
