#pragma once
#include "GameObject.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "Player.h"
#include "UIManager.h"

class StageManager
{
private:
	Stage* _currStage;
	Player* _player;
	UIManager* _uiManager;

public:
	void init();

	void release();

	void update();

	void render();

	void moveGameObject(GameObject& gameObject, Vector3 moveDir) { _currStage->moveGameObject(gameObject, moveDir); }
	void setPlayer(Player* player) { _player = player; }
	void setUIManager(UIManager* uiManager) { _uiManager = uiManager; }
};

