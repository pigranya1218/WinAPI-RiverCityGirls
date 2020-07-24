#pragma once
#include "GameObject.h"
#include "Object.h"
#include "Player.h"

class StageManager;

class ObjectManager :  public GameObject
{
private:
	StageManager* _stageManager;
	vector<Object*> _objects;

public:
	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setStageManager(StageManager* stageManager) { _stageManager = stageManager; }

	void collision(Vector3* pos, GameObject* gameObject);

	void spawnObject(OBJECT_TYPE type, Vector3 pos, DIRECTION direction);
	void makeParticle(PARTICLE_TYPE type, int num, Vector3 minPos, Vector3 maxPos, Vector2 minAngle, Vector2 maxAngle, float minSpeed, float maxSpeed, float minTime, float maxTime);

	void getHit(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type);

	void moveGameObject(GameObject* gameObject, Vector3 move);
};

