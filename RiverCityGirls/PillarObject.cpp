#include "stdafx.h"
#include "PillarObject.h"
#include "ObjectManager.h"

PillarObject::PillarObject(Vector3 position, DIRECTION direction)
{
	_direction = direction;
	_size = Vector3(110, 800, 55);
	_position = Vector3(position.x, -(_size.y / 2), position.z);

	switch (_direction)
	{
		case DIRECTION::RIGHT:
		{_img = IMAGE_MANAGER->findImage("OBJECT_PILLAR_RIGHT"); }
		break;
		case DIRECTION::LEFT:
		{_img = IMAGE_MANAGER->findImage("OBJECT_PILLAR_LEFT"); }
		break;
	}

	int linePos[4][4] = { {_position.x - (_size.x / 2) + (_size.z / 2) , _position.z - (_size.z / 2), _position.x + (_size.x / 2) + (_size.z / 2), _position.z - (_size.z / 2)}, // ��
						{_position.x - (_size.x / 2) - (_size.z / 2), _position.z + (_size.z / 2), _position.x + (_size.x / 2) - (_size.z / 2), _position.z + (_size.z / 2)}, }; // ��
	linePos[2][0] = linePos[1][0]; // ��
	linePos[2][1] = linePos[1][1];
	linePos[2][2] = linePos[0][0];
	linePos[2][3] = linePos[0][1];
	linePos[3][0] = linePos[1][2]; // ��
	linePos[3][1] = linePos[1][3];
	linePos[3][2] = linePos[0][2];

	if (_direction == DIRECTION::LEFT)
	{
		_restrictRect = new RestrictMoveRect(Vector2(_position.x + _collisionOffsetX - (_size.x / 2) + (_size.z / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// LT
			Vector2(_position.x + _collisionOffsetX + (_size.x / 2) + (_size.z / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// RT
			Vector2(_position.x + _collisionOffsetX + (_size.x / 2) - (_size.z / 2), _position.z + _collisionOffsetZ + (_size.z / 2)),		// RB
			Vector2(_position.x + _collisionOffsetX - (_size.x / 2) - (_size.z / 2), _position.z + _collisionOffsetZ + (_size.z / 2)), _size.y);		// LB
	}
	else if (_direction == DIRECTION::RIGHT)
	{
		_restrictRect = new RestrictMoveRect(Vector2(_position.x - _collisionOffsetX - (_size.x / 2) - (_size.z / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// LT
			Vector2(_position.x - _collisionOffsetX + (_size.x / 2) - (_size.z / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// RT
			Vector2(_position.x - _collisionOffsetX + (_size.x / 2) + (_size.z / 2), _position.z + _collisionOffsetZ + (_size.z / 2)),		//RB
			Vector2(_position.x - _collisionOffsetX - (_size.x / 2) + (_size.z / 2), _position.z + _collisionOffsetZ + (_size.z / 2)), _size.y);		// LB
	}
}

void PillarObject::update()
{
}

void PillarObject::release()
{
	delete _restrictRect;
}

void PillarObject::render()
{
	Object::render();

	_img->setScale(3);
	CAMERA_MANAGER->renderZ(_img, _position, _size);

	if (DEBUG_MANAGER->isDebugMode(DEBUG_TYPE::OBJECT))
	{
		_restrictRect->render();
	}
}

void PillarObject::collision(Vector3 * newPoses, GameObject* gameObject)
{
	_restrictRect->checkCollision(newPoses, gameObject);
}

void PillarObject::hitEffect(GameObject * hitter, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	if (hitter->getTeam() != OBJECT_TEAM::PLAYER) return; // �ϴ� �÷��̾ ���� �� �ƴ϶�� �н�

	if (_state != OBJECT_STATE::INACTIVE)
	{
		_objectManager->makeParticle(PARTICLE_TYPE::PIECE_PILLAR, 20,
			Vector3(_position.x - (_size.x / 2), _position.y, _position.z),
			Vector3(_position.x + (_size.x / 2), _position.y + (_size.y / 2), _position.z + (_size.z / 2)),
			Vector2(0, 0),
			Vector2(PI2, PI),
			5, 6, 1, 3);
		_state = OBJECT_STATE::INACTIVE;

	}
}

