#pragma once
#include "GameObject.h"
#include "Stage.h"
#include "ObjectManager.h"

class StageManager
{
private:
	Stage* _currStage;
	ObjectManager* _objectMg;

	// DEBEG
	GameObject* _dummy;

public:
	void init();

	void release();

	void update();

	void render();

	void moveGameObject(GameObject& gameObject, Vector3 moveDir) { _currStage->moveGameObject(gameObject, moveDir); }
};

