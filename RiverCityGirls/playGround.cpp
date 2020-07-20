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


	// ��� �� SCENE_MANAGER�� ���
	SCENE_MANAGER->addScene("MAIN", new MainScene);
	SCENE_MANAGER->addScene("STAGE", new StageScene);
	SCENE_MANAGER->changeScene("MAIN");

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
	D2D_RENDERER->beginRender(D2D1::ColorF::White);
	{
		SCENE_MANAGER->render();

		CAMERA_MANAGER->renderZList();
	}
	//����ۿ� �׸� ������� ȭ�鿡 �ѷ���~
	D2D_RENDERER->endRender();
}
