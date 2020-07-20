#include "stdafx.h"
#include "PlayGround.h"

#include "MainScene.h"
#include "StageScene.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ �Լ�
HRESULT playGround::init()
{
	GameNode::init(true);

	// ��� �̹��� IMAGE_MANAGER�� ���
	
	// * ��������
	// ** �������� ��� �̹��� �߰�
	IMAGE_MANAGER->addImage("STAGE_1", L"resources/images/stages/stage_1.png");
	IMAGE_MANAGER->addImage("STAGE_2", L"resources/images/stages/stage_2.png");
	IMAGE_MANAGER->addImage("STAGE_BOSS_BEFORE", L"resources/images/stages/stage_boss_before.png");
	IMAGE_MANAGER->addImage("STAGE_BOSS_AFTER", L"resources/images/stages/stage_boss_after.png");


	// ��� �� SCENE_MANAGER�� ���
	SCENE_MANAGER->addScene("MAIN", new MainScene);
	SCENE_MANAGER->addScene("STAGE", new StageScene);
	SCENE_MANAGER->changeScene("STAGE");

	return S_OK;
}

//�޸� ����
void playGround::release()
{
	GameNode::release();
}

//����
void playGround::update()
{
	GameNode::update();

	SCENE_MANAGER->update();
}

//�׸��� ����
void playGround::render()
{	
	//����� �ʱ�ȭ
	D2D_RENDERER->beginRender(D2D1::ColorF::Black);
	{
		SCENE_MANAGER->render();

	}
	//����ۿ� �׸� ������� ȭ�鿡 �ѷ���~
	D2D_RENDERER->endRender();
}
