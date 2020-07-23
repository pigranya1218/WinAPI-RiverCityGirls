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

	void collision(Vector3* pos, GameObject* gameObject);

	//				오브젝트 종류 type,		위치 pos,		방향	 direction			,이미지 종류 imageType 0
	void spawnObject(OBJECT_TYPE type, Vector3 pos, DIRECTION direction, int imageType);
};

