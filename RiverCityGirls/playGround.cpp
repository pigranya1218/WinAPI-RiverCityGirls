#include "stdafx.h"
#include "PlayGround.h"

#include "EventManager.h"
#include "IEvent.h"
#include "MainScene.h"
#include "StageScene.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화 함수
HRESULT playGround::init()
{
	GameNode::init(true);

	// 모든 이미지 IMAGE_MANAGER에 등록
	IMAGE_MANAGER->addImage("TestObject", L"TrapObject.png");
	IMAGE_MANAGER->addFrameImage("TestFrameObject", L"Bomb.png", 3, 1);

	// 모든 씬 SCENE_MANAGER에 등록
	SCENE_MANAGER->addScene("MAIN", new MainScene);
	SCENE_MANAGER->addScene("STAGE", new StageScene);
	SCENE_MANAGER->changeScene("MAIN");

	return S_OK;
}

//메모리 해제
void playGround::release()
{
	GameNode::release();
}

//연산
void playGround::update()
{
	GameNode::update();

	SCENE_MANAGER->update();
	
	// EventManager::getInstance()->update();
}

//그리기 전용
void playGround::render()
{	
	//백버퍼 초기화
	D2D_RENDERER->beginRender(D2D1::ColorF::Black);
	{
		SCENE_MANAGER->render();

		CAMERA_MANAGER->renderZList();
	}
	//백버퍼에 그린 내용들을 화면에 뿌려라~
	D2D_RENDERER->endRender();
}
