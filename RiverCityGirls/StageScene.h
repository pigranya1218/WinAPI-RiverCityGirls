#pragma once
#include "GameNode.h"
#include "StageManager.h"'
#include "UIManager.h"
#include "Player.h"

class StageScene : public GameNode
{
private:
	StageManager* _stageManager;
	UIManager* _uiManager;
	Player* _player;

public:
	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� ����
	virtual void update();			//���� ����
	virtual void render();			//�׸��� ����
};

