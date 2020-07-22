#pragma once
#include "GameObject.h"
#include "Object.h"
#include "Player.h"

enum class OBJECT_TYPE
{
	DESK, BOX, DESK_CHAIR, TEACHER_TABLE, TABLE, TABLE_CHAIR, PILLAR, SNACKMACHINE, LOCKER, mrRudis, schoolBoyA, schoolBoyB, schoolBoyE, schoolGirlA, schoolGirlB, schoolGirlE, workingFemaleA, workingMaleD
};


class ObjectManager :  public GameObject
{
private:
	vector<Object*> _objects;

public:
	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();

	void spawnObject(OBJECT_TYPE type, Vector3 pos, DIRECTION direction);
};

