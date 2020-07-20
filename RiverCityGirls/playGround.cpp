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

	IMAGE_MANAGER->addFrameImage("쿄코대기", L"Kyoko/Kyoko_idle.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("쿄코걷기", L"Kyoko/Kyoko_walk.png",12,2);
	IMAGE_MANAGER->addFrameImage("쿄코달리기", L"Kyoko/Kyoko_run.png", 16, 2);
	IMAGE_MANAGER->addFrameImage("쿄코점프", L"Kyoko/Kyoko_jump.png", 3, 2);

	_kyoko = new Kyoko;
	_kyoko->init();

	/*IMAGE_MANAGER->AddImage("TestObject", L"TrapObject.png");
	IMAGE_MANAGER->AddFrameImage("TestFrameObject",
		L"Bomb.png", 3, 1);
	//Enemy 이미지 
	//*스쿨보이
	IMAGE_MANAGER->addFrameImage("스쿨보이_공격1", L"images/enemy_schoolboy/SchoolBoyAttack1.png", 7, 2);
	IMAGE_MANAGER->addFrameImage("스쿨보이_공격2", L"images/enemy_schoolboy/SchoolBoyAttack2.png", 7, 2);
	IMAGE_MANAGER->addFrameImage("스쿨보이_공격3", L"images/enemy_schoolboy/SchoolBoyAttack3.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("스쿨보이_항복", L"images/enemy_schoolboy/SchoolBoybegging.png", 2, 2);
	IMAGE_MANAGER->addFrameImage("스쿨보이_가드", L"images/enemy_schoolboy/SchoolBoyBlock.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("스쿨보이_피격", L"images/enemy_schoolboy/SchoolBoyGetHit.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("스쿨보이_그라운드피격", L"images/enemy_schoolboy/SchoolBoyGroundHit.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("스쿨보이_속박피격", L"images/enemy_schoolboy/SchoolBoyHeldHit.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("스쿨보이_속박해제", L"images/enemy_schoolboy/SchoolBoyHeldRelease.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("스쿨보이_기본", L"images/enemy_schoolboy/SchoolBoyIdle.png", 8, 2);
	IMAGE_MANAGER->addFrameImage("스쿨보이_점프", L"images/enemy_schoolboy/SchoolBoyJump.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("스쿨보이_점프공격", L"images/enemy_schoolboy/SchoolBoyJumpPunch.png", 6, 2);
	IMAGE_MANAGER->addFrameImage("스쿨보이_다운", L"images/enemy_schoolboy/SchoolBoyKcockDown.png", 33, 2);
	IMAGE_MANAGER->addFrameImage("스쿨보이_달리기", L"images/enemy_schoolboy/SchoolBoyRun.png", 10, 2);
	IMAGE_MANAGER->addFrameImage("스쿨보이_모래뿌리기", L"images/enemy_schoolboy/SchoolBoySandToss.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("스쿨보이_스턴", L"images/enemy_schoolboy/SchoolBoyStun.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("스쿨보이_걷기", L"images/enemy_schoolboy/SchoolBoyWalk.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("스쿨보이_대시공격", L"images/enemy_schoolboy/SchoolDashAttack.png", 7, 2);
	//*스쿨걸
	IMAGE_MANAGER->addFrameImage("스쿨걸_피격_다운", L"images/enemy_schoolgirl/blowBack.png", 33, 2);
	IMAGE_MANAGER->addFrameImage("스쿨걸_피격", L"images/enemy_schoolgirl/getHit.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("스쿨걸_속박피격", L"images/enemy_schoolgirl/HeldHit.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("스쿨걸_속박해제", L"images/enemy_schoolgirl/잡기 풀기.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("스쿨걸_기본", L"images/enemy_schoolgirl/Idle.png", 10, 2);
	IMAGE_MANAGER->addFrameImage("스쿨걸_다운", L"images/enemy_schoolgirl/knokBack.png", 33, 2);
	IMAGE_MANAGER->addFrameImage("스쿨걸_스턴", L"images/enemy_schoolgirl/stun.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("스쿨걸_걷기", L"images/enemy_schoolgirl/Walk.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("스쿨걸_달리기", L"images/enemy_schoolgirl/run.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("스쿨걸_가드", L"images/enemy_schoolgirl/가드.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("스쿨걸_그라운드피격", L"images/enemy_schoolgirl/그라운드 히트.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("스쿨걸_공격1", L"images/enemy_schoolgirl/잽.png", 8, 2);
	IMAGE_MANAGER->addFrameImage("스쿨걸_공격2", L"images/enemy_schoolgirl/니킥.png", 7, 2);
	IMAGE_MANAGER->addFrameImage("스쿨걸_공격3", L"images/enemy_schoolgirl/발차기.png", 8, 2);
	IMAGE_MANAGER->addFrameImage("스쿨걸_회전킥", L"images/enemy_schoolgirl/회전킥.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("스쿨걸_점프", L"images/enemy_schoolgirl/점프.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("스쿨걸_항복", L"images/enemy_schoolgirl/항복.png", 3, 2);


	/*_enemyMg = new enemyManager;
	_enemyMg->init();*/
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

	_kyoko->update();

	/*SCENE_MANAGER->update();
	UI_MANAGER->update();

	static float hp = 100;
	if (hp < 0) hp = 100;
	hp -= 0.5f;
	UI_MANAGER->setBossHp(hp, 100.0f);	
	UI_MANAGER->setPlayerHp(hp, 100.0f);*/
}

//그리기 전용
void playGround::render()
{	
	//백버퍼 초기화
	D2D_RENDERER->beginRender(D2D1::ColorF::Black);
	{

		_kyoko->render();
		/*SCENE_MANAGER->render();
		UI_MANAGER->render();		
*/
	}
	//백버퍼에 그린 내용들을 화면에 뿌려라~
	D2D_RENDERER->endRender();
}
