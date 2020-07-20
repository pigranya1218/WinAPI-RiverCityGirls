#pragma once
#include "linearFunc.h"
#include "GameObject.h"

class StageManager;
class ObjectManager;

class Stage
{
private:
	struct tagDontMove // 스테이지 이동 영역을 제한하기 위한 구조체
	{
		LinearFunc line; // 선분
		LINEAR_VALUE_TYPE type; // 이 선분 어디를 못지나가게 할 것인가?
	};
private:
	StageManager* _stageManager; 
	ObjectManager* _objectManager; 
	
	Image* _background;
	vector<tagDontMove> _linearFuncs; // 스테이지의 이동 영역을 제한

public:
	virtual void init(Image* background) { _background = background; };
	virtual void enter() {};
	virtual void exit() {};
	virtual Stage* update() { return nullptr; };
	virtual void render();

	void setStageManager(StageManager* stageManager) { _stageManager = stageManager; }

	void pushLine(LinearFunc line, LINEAR_VALUE_TYPE type) { _linearFuncs.push_back({ line, type }); }

	// 게임 오브젝트를 가능한만큼 이동시킴
	void moveGameObject(GameObject& gameObject, Vector3 move);
	
};