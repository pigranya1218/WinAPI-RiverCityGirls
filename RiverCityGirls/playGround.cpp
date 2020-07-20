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

//초기화 함수
HRESULT playGround::init()
{
	GameNode::init(true);

	// 모든 이미지 IMAGE_MANAGER에 등록
	// * 스테이지
	// ** 스테이지 배경 이미지 추가
	IMAGE_MANAGER->addImage("STAGE_1", L"resources/images/stages/stage_1.png");
	IMAGE_MANAGER->addImage("STAGE_2", L"resources/images/stages/stage_2.png");
	IMAGE_MANAGER->addImage("STAGE_BOSS_BEFORE", L"resources/images/stages/stage_boss_before.png");
	IMAGE_MANAGER->addImage("STAGE_BOSS_AFTER", L"resources/images/stages/stage_boss_after.png");
	IMAGE_MANAGER->addImage("screenBorder", L"resources/images/UI/playBorder.png");					// 플레이화면 테두리

	IMAGE_MANAGER->addImage("playerBackBar"	, L"resources/images/UI/UI_Player_HP_BackBar.png");		// 플레이어 체력 뒤
	IMAGE_MANAGER->addImage("playerFrontBar", L"resources/images/UI/UI_Player_HP_FrontBar.png");	// 플레이어 체력 앞
	IMAGE_MANAGER->addImage("playerHpFrame"	, L"resources/images/UI/UI_Player_Bar.png");			// 플레이어 체력 프레임
	IMAGE_MANAGER->addImage("kyokoShot"		, L"resources/images/UI/UI_kyoko_shot.png");			// 플레이어 체력 옆 이미지

	IMAGE_MANAGER->addImage("bossBackBar"	, L"resources/images/UI/UI_Boss_HP_BackBar.png");		// 보스 체력 뒤
	IMAGE_MANAGER->addImage("bossFrontBar"	, L"resources/images/UI/UI_Boss_HP_FrontBar.png");		// 보스 체력 앞
	IMAGE_MANAGER->addImage("bossHpFrame"	, L"resources/images/UI/UI_Boss_HP_Frame.png");			// 보스 체력 프레임

	IMAGE_MANAGER->addImage("startMapPhone", L"resources/images/UI/startStage_phone.png");			// 핸드폰 이미지

	
	
	IMAGE_MANAGER->addImage("unlockDoor", L"resources/images/UI/UI_UNLOCKED_DOOR.png");				// 열린 문
	IMAGE_MANAGER->addImage("lockDoor"	, L"resources/images/UI/UI_LOCKED_DOOR.png");				// 닫힌 문
	
	


	// 모든 씬 SCENE_MANAGER에 등록
	SCENE_MANAGER->addScene("MAIN", new MainScene);
	SCENE_MANAGER->addScene("STAGE", new StageScene);
	SCENE_MANAGER->changeScene("STAGE");

	// UI 테스트용
	UI_MANAGER->init();
	UI_MANAGER->setBossHpActive(true);
	UI_MANAGER->setPlayerHp(100.0f, 100.0f);
	UI_MANAGER->setPlayerHpActive(true);
	UI_MANAGER->setBossHp(100.0f, 100.0f);

	UI_MANAGER->setDoorLock(true, Vector2(WINSIZEX / 2, WINSIZEY / 2), currentDoor::UNLOCK, 0.5f);


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
	UI_MANAGER->update();

	static float hp = 100;
	if (hp < 0) hp = 100;
	hp -= 0.5f;
	UI_MANAGER->setBossHp(hp, 100.0f);	
	UI_MANAGER->setPlayerHp(hp, 100.0f);
}

//그리기 전용
void playGround::render()
{	
	//백버퍼 초기화
	D2D_RENDERER->beginRender(D2D1::ColorF::Black);
	{
		SCENE_MANAGER->render();
		UI_MANAGER->render();		

	}
	//백버퍼에 그린 내용들을 화면에 뿌려라~
	D2D_RENDERER->endRender();
}
