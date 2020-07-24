#include "stdafx.h"
#include "ParticleObject.h"
#include "ObjectManager.h"

ParticleObject::ParticleObject(PARTICLE_TYPE type, Vector3 pos, Vector2 angle, float speed, float time)
{
	_type = type;
	char buffer[50];
	switch (_type)
	{
		case PARTICLE_TYPE::PIECE_SNACKMACHINE:
		{
			int randomImageNum = RANDOM->getInt(4) + 1;
			sprintf_s(buffer, "OBJECT_SNACKMACHINE_PIECE0%d", randomImageNum);
			_img = IMAGE_MANAGER->findImage(buffer);
		}
		break;
		case PARTICLE_TYPE::PIECE_PILLAR:
		{
			int randomImageNum = RANDOM->getInt(3) + 1;
			sprintf_s(buffer, "OBJECT_PILLAR_PIECE0%d", randomImageNum);
			_img = IMAGE_MANAGER->findImage(buffer);
		}
		break;
	}
	
	_state = OBJECT_STATE::IDLE;
	_position = pos;
	_size = Vector3(2, 2, 2);
	_moveAngle = angle;
	_speed = speed;
	_remainTime = time;
	_gravity = 0;
}

void ParticleObject::update()
{
	_gravity += 0.08f;
	_rotateAngle += 3;

	Vector3 moveDir = Vector3(0, 0, 0); // [0, 0, 0]
	moveDir.x += cosf(_moveAngle.x) * _speed;
	moveDir.z += -sinf(_moveAngle.x) * _speed;
	moveDir.y += -sinf(_moveAngle.y) * _speed + _gravity;
	
	_position += moveDir;
	_position.y = max(-(_size.y / 2), _position.y);

	_remainTime -= TIME_MANAGER->getElapsedTime();
	if (_remainTime <= 0)
	{
		_state = OBJECT_STATE::INACTIVE;
	}
}

void ParticleObject::release()
{
}

void ParticleObject::render()
{
	_img->setScale(2);
	_img->setAngle(_rotateAngle);

	CAMERA_MANAGER->renderZ(_img, _position, _size);
}
