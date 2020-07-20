#pragma once
#include "GameObject.h"
#include "Stage.h"

class StageManager
{
private:
	Stage* _currStage;

public:
	void init();

	void release();

	void update();

	void render();

	void moveGameObject(GameObject& gameObject, Vector3 moveDir) { _currStage->moveGameObject(gameObject, moveDir); }
};

