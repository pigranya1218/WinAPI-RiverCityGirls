#pragma once
#include "GameNode.h"
#include "StageManager.h"'

class StageScene : public GameNode
{
private:
	StageManager* _stageManager;

public:
	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� ����
	virtual void update();			//���� ����
	virtual void render();			//�׸��� ����
};

