#pragma once
#include "linearFunc.h"
#include "GameObject.h"

class StageManager;
class ObjectManager;

class Stage
{
private:
	struct tagDontMove // �������� �̵� ������ �����ϱ� ���� ����ü
	{
		LinearFunc line; // ����
		LINEAR_VALUE_TYPE type; // �� ���� ��� ���������� �� ���ΰ�?
	};
private:
	StageManager* _stageManager; 
	ObjectManager* _objectManager; 
	
	Image* _background;
	vector<tagDontMove> _linearFuncs; // ���������� �̵� ������ ����

public:
	virtual void init(Image* background) { _background = background; };
	virtual void enter() {};
	virtual void exit() {};
	virtual Stage* update() { return nullptr; };
	virtual void render();

	void setStageManager(StageManager* stageManager) { _stageManager = stageManager; }

	void pushLine(LinearFunc line, LINEAR_VALUE_TYPE type) { _linearFuncs.push_back({ line, type }); }

	// ���� ������Ʈ�� �����Ѹ�ŭ �̵���Ŵ
	void moveGameObject(GameObject& gameObject, Vector3 move);
	
};