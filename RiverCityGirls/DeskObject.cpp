#include "stdafx.h"
#include "DeskObject.h"

DeskObject::DeskObject(Vector3 position, DIRECTION direction)
{
	_direction = direction;
	_size = Vector3(80, 80, 60);
	_position = Vector3(position.x, -(_size.y / 2), position.z);

	_img = IMAGE_MANAGER->findImage("OBJECT_DESK");

	int linePos[4][4] = { {_position.x - (_size.x / 2) + (_size.z / 2) , _position.z - (_size.z / 2), _position.x + (_size.x / 2) + (_size.z / 2), _position.z - (_size.z / 2)}, // ╩С
						{_position.x - (_size.x / 2) - (_size.z / 2), _position.z + (_size.z / 2), _position.x + (_size.x / 2) - (_size.z / 2), _position.z + (_size.z / 2)}, }; // го
	linePos[2][0] = linePos[1][0]; // аб
	linePos[2][1] = linePos[1][1];
	linePos[2][2] = linePos[0][0];
	linePos[2][3] = linePos[0][1];
	linePos[3][0] = linePos[1][2]; // ©Л
	linePos[3][1] = linePos[1][3];
	linePos[3][2] = linePos[0][2];

	_restrictRect = new RestrictMoveRect(Vector2(_position.x + _collisionOffsetX - (_size.x / 2) + (_size.z / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// LT
										Vector2(_position.x + _collisionOffsetX + (_size.x / 2) + (_size.z / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// RT
										Vector2(_position.x + _collisionOffsetX + (_size.x / 2) - (_size.z / 2), _position.z + _collisionOffsetZ + (_size.z / 2)),		// RB
									Vector2(_position.x + _collisionOffsetX - (_size.x / 2) - (_size.z / 2), _position.z + _collisionOffsetZ + (_size.z / 2)),
									_size.y);		// LB
}


void DeskObject::update()
{
	//_img->setScale(3);
}

void DeskObject::release()
{
	delete _restrictRect;
}

void DeskObject::render()
{
	_img->setScale(3);
	_img->setAlpha(1);
	CAMERA_MANAGER->renderZ(_img, _position, _size, -(_size.z / 2));

	_restrictRect->render();
	CAMERA_MANAGER->drawLine(Vector2(_position.x + _collisionOffsetX, _position.z + _collisionOffsetZ), Vector2(_position.x + _collisionOffsetX, _position.z + _collisionOffsetZ - _size.y));
}

void DeskObject::collision(Vector3 * newPoses, GameObject* gameObject)
{
	_restrictRect->checkCollision(newPoses, gameObject);
}

