#include "stdafx.h"
#include "SnackMachineObject.h"

SnackMachineObject::SnackMachineObject(Vector3 position, DIRECTION direction)
{
	_direction = direction;
	_size = Vector3(190, 190, 55);
	_position = Vector3(position.x, -(_size.y / 2), position.z);

	if (_direction == DIRECTION::LEFT)
	{
		_img = IMAGE_MANAGER->findImage("OBJECT_SNACKMACHINE_LEFT");
	}
	if (_direction == DIRECTION::RIGHT)
	{
		_img = IMAGE_MANAGER->findImage("OBJECT_SNACKMACHINE_RIGHT");
	}

	int linePos[4][4] = { {_position.x - (_size.x / 2) + (_size.z / 2) , _position.z - (_size.z / 2), _position.x + (_size.x / 2) + (_size.z / 2), _position.z - (_size.z / 2)}, // ╩С
						{_position.x - (_size.x / 2) - (_size.z / 2), _position.z + (_size.z / 2), _position.x + (_size.x / 2) - (_size.z / 2), _position.z + (_size.z / 2)}, }; // го
	linePos[2][0] = linePos[1][0]; // аб
	linePos[2][1] = linePos[1][1];
	linePos[2][2] = linePos[0][0];
	linePos[2][3] = linePos[0][1];
	linePos[3][0] = linePos[1][2]; // ©Л
	linePos[3][1] = linePos[1][3];
	linePos[3][2] = linePos[0][2];

	if (_direction == DIRECTION::LEFT)
	{
		_restrictRect = new RestrictMoveRect(Vector2(_position.x + _collisionOffsetX - (_size.x / 2) + (_size.z / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// LT
			Vector2(_position.x + _collisionOffsetX + (_size.x / 2) + (_size.z / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// RT
			Vector2(_position.x + _collisionOffsetX + (_size.x / 2) - (_size.z / 2), _position.z + _collisionOffsetZ + (_size.z / 2)),		// RB
			Vector2(_position.x + _collisionOffsetX - (_size.x / 2) - (_size.z / 2), _position.z + _collisionOffsetZ + (_size.z / 2)), _size.y);		// LB
	}
	//if (_direction == DIRECTION::RIGHT)
	//{
	//	_restrictRect = new RestrictMoveRect(Vector2(_position.x + _collisionOffsetX - (_size.x / 2) + (_size.z / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// LT
	//		Vector2(_position.x + _collisionOffsetX + (_size.x / 2) + (_size.z / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// RT
	//		Vector2(_position.x + _collisionOffsetX + (_size.x / 2) + (_size.z * 2), _position.z + _collisionOffsetZ + (_size.z / 2)),		//RB
	//		Vector2(_position.x + _collisionOffsetX + (_size.x / 2) - (_size.z / 2), _position.z + _collisionOffsetZ + (_size.z / 2)), _size.y);		// LB
	//		//Vector2(_position.x + _collisionOffsetX - (_size.x / 2) - (_size.z / 2), _position.z + _collisionOffsetZ + (_size.z / 2)), _size.y);		// 
	//}
}

void SnackMachineObject::update()
{
}

void SnackMachineObject::release()
{
	delete _restrictRect;
}

void SnackMachineObject::render()
{
	Object::render();

	CAMERA_MANAGER->renderZ(_img, _position, _size);

	if (DEBUG_MANAGER->isDebugMode(DEBUG_TYPE::OBJECT))
	{
		_restrictRect->render();
	}
}

void SnackMachineObject::collision(Vector3 * newPoses, GameObject* gameObject)
{
	_restrictRect->checkCollision(newPoses, gameObject);
}

void SnackMachineObject::hitEffect(GameObject * hitter, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	if (_state != OBJECT_STATE::BROKEN)
	{
		_state = OBJECT_STATE::BROKEN;
		if (_direction == DIRECTION::LEFT)
		{
			_img = IMAGE_MANAGER->findImage("OBJECT_SNACKMACHINE_LEFT_BROKEN");
		}
		if (_direction == DIRECTION::RIGHT)
		{
			_img = IMAGE_MANAGER->findImage("OBJECT_SNACKMACHINE_RIGHT_BROKEN");
		}
	}
}