#pragma once
#include "Object.h"
class ParticleObject :  public Object
{
private:
	Vector2 _moveAngle;				// �̵� ����
	float _speed;					// �̵� �ӵ�
	float _rotateAngle;			// ȸ������
	float _gravity;					// �߷�
	float _remainTime;				// ���̴� �ð�
	bool _isLand; // �����Ͽ���
	PARTICLE_TYPE _type;			// ������ Ÿ��

public:
	ParticleObject(PARTICLE_TYPE type, Vector3 pos, Vector2 angle, float speed, float time);
	virtual void update();
	virtual void release();
	virtual void render();
};

