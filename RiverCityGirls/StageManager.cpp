#include "stdafx.h"
#include "StageManager.h"
#include "NormalStage.h"
#include "BossStage.h"


void StageManager::init()
{
	// ��� ������������ ������ ������ ���Ϸκ��� �а� ������ ����
	
	// DEBUG
	_currStage = new NormalStage;
	_currStage->init(IMAGE_MANAGER->findImage("STAGE_1"), 3);
	_currStage->setStageManager(this);
	_currStage->setPlayer(_player);

	_dummy = new GameObject;
	Vector3 pos; // ��ġ
	pos.x = 400; 
	pos.y = 0;
	pos.z = 400;
	_dummy->SetPosition(pos);
	Vector3 size; // �浹 ũ��
	size.x = 50;
	size.y = 50;
	size.z = 50;
	Vector2 sizeV2; // �׸���
	sizeV2.x = 50;
	sizeV2.y = 50;
	_dummy->SetSize(size);
	_dummy->SetRect(rectMakePivot(CAMERA_MANAGER->convertV3ToV2(pos), sizeV2, Pivot::Center));
}

void StageManager::release()
{
}

void StageManager::update()
{
	Stage* newStage = _currStage->update();
	if (newStage != nullptr)
	{
		_currStage->exit();
		_currStage = newStage;
		_currStage->enter();
	}

	Vector3 dir;
	dir.x = 0;
	dir.y = 0;
	dir.z = 0;

	if (KEY_MANAGER->isStayKeyDown(VK_LEFT))
	{
		dir.x -= 4;
	}
	if (KEY_MANAGER->isStayKeyDown(VK_RIGHT))
	{
		dir.x += 4;
	}
	if (KEY_MANAGER->isStayKeyDown(VK_UP))
	{
		dir.z -= 4;
	}
	if (KEY_MANAGER->isStayKeyDown(VK_DOWN))
	{
		dir.z += 4;
	}
	moveGameObject(*_dummy, dir);
	_dummy->update();

	CAMERA_MANAGER->setXY(CAMERA_MANAGER->convertV3ToV2(_dummy->GetPosition()));
}

void StageManager::render()
{
	_currStage->render();
	
	FloatRect fr = _dummy->GetRect();
	CAMERA_MANAGER->rectangle(fr, D2D1::ColorF::Enum::Black, 1, 5);

	CAMERA_MANAGER->renderZList();
}
