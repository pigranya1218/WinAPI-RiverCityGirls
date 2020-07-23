#pragma once
#include "GameObject.h"
#include "Object.h"
#include "Player.h"

enum class OBJECT_TYPE
{
	DESK01, DESK02, DESK03, BOX, DESK_CHAIR01, DESK_CHAIR02, TABLE_CHAIR01, TABLE_CHAIR02, 
	TEACHER_TABLE,
	TABLE01, TABLE02, TABLE03, TABLE04, TABLE05, TABLE06, TABLE07, TABLE08,
	PILLAR, SNACKMACHINE,
	LOCKER, 
	mrRudis, schoolBoyA_idle01, schoolBoyA_idle02,
	schoolBoyB_idle01, schoolBoyB_idle02,
	schoolBoyE_idle01, schoolBoyE_idle02,
	schoolGirlA_idle01, schoolGirlA_idle02,
	schoolGirlB_idle01, schoolGirlB_idle02,
	schoolGirlE_idle01, schoolGirlE_idle02,
	workingFemaleA, workingMaleD
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

	void spawnObject(OBJECT_TYPE type, Vector3 pos, DIRECTION direction);

	void getHit(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type);
};

