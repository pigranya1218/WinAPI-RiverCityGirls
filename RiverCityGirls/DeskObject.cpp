#include "stdafx.h"
#include "DeskObject.h"

DeskObject::DeskObject(Vector3 position, DIRECTION direction)
{
	_direction = direction;
	_size = Vector3(120, 80, 80);
	_position = Vector3(position.x, -(_size.y / 2), position.z);

	_img = IMAGE_MANAGER->findImage("OBJECT_DESK");

	int linePos[4][4] = { {_position.x - (_size.x / 2) + (_size.z / 2) , _position.z - (_size.z / 2), _position.x + (_size.x / 2) + (_size.z / 2), _position.z - (_size.z / 2)}, // ��
						{_position.x - (_size.x / 2) - (_size.z / 2), _position.z + (_size.z / 2), _position.x + (_size.x / 2) - (_size.z / 2), _position.z + (_size.z / 2)}, }; // ��
	linePos[2][0] = linePos[1][0]; // ��
	linePos[2][1] = linePos[1][1];
	linePos[2][2] = linePos[0][0];
	linePos[2][3] = linePos[0][1];
	linePos[3][0] = linePos[1][2]; // ��
	linePos[3][1] = linePos[1][3];
	linePos[3][2] = linePos[0][2];
	linePos[3][3] = linePos[0][3];

	int lineRange[4][4] = { {linePos[0][0], linePos[0][2], linePos[0][1], linePos[1][1]}, // ��
							{linePos[1][0], linePos[1][2], linePos[0][1], linePos[1][1]}, // ��
							{linePos[2][0], linePos[2][2], linePos[0][1], linePos[1][1]}, // �� 
							{linePos[3][0], linePos[3][2], linePos[0][1], linePos[1][1]} }; // ��

	_restrictRect = new RestrictMoveRect(Vector2(_position.x - (_size.x / 2) + (_size.z / 2), _position.z - (_size.z / 2)),		// LT
										Vector2(_position.x + (_size.x / 2) + (_size.z / 2), _position.z - (_size.z / 2)),		// RT
										Vector2(_position.x + (_size.x / 2) - (_size.z / 2), _position.z + (_size.z / 2)),		// RB
										Vector2(_position.x - (_size.x / 2) - (_size.z / 2), _position.z + (_size.z / 2)));		// LB
}


void DeskObject::update()
{

}

void DeskObject::release()
{
	delete _restrictRect;
}

void DeskObject::render()
{
	_img->setScale(3);
	_img->setAlpha(0.5);
	CAMERA_MANAGER->renderZ(_img, _position, _size, false);

	_restrictRect->render();
	CAMERA_MANAGER->drawLine(Vector2(_position.x, _position.z), Vector2(_position.x, _position.z - _size.y));
}

void DeskObject::collision(Vector3 * newPoses, Vector3 size)
{
	_restrictRect->checkCollision(newPoses, size);
}
