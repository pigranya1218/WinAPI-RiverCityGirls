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
	
	// * Object
	// ** DESK
	IMAGE_MANAGER->addImage("OBJECT_DESK", L"resources/images/object/03_Detention_OBJ_Desks_01.png");

	// * Player
	IMAGE_MANAGER->addFrameImage("Kyoko_idle", L"images/kyoko/Kyoko_idle.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_walk", L"images/kyoko/Kyoko_walk.png",12,2);
	IMAGE_MANAGER->addFrameImage("Kyoko_run", L"images/kyoko/Kyoko_run.png", 16, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_jump", L"images/kyoko/Kyoko_jump.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_walljump", L"images/kyoko/Kyoko_walljump.png", 2, 2);

	// * Enemy 
    // ** schoolBoy
	IMAGE_MANAGER->addFrameImage("schoolboy_attack1", L"images/enemy_schoolboy/SchoolBoyAttack1.png", 7, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_attack2", L"images/enemy_schoolboy/SchoolBoyAttack2.png", 7, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_attack3", L"images/enemy_schoolboy/SchoolBoyAttack3.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_begging", L"images/enemy_schoolboy/SchoolBoybegging.png", 2, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_block", L"images/enemy_schoolboy/SchoolBoyBlock.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_getHit", L"images/enemy_schoolboy/SchoolBoyGetHit.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_groundHit", L"images/enemy_schoolboy/SchoolBoyGroundHit.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_heldHit", L"images/enemy_schoolboy/SchoolBoyHeldHit.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_heldRelease", L"images/enemy_schoolboy/SchoolBoyHeldRelease.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_idle", L"images/enemy_schoolboy/SchoolBoyIdle.png", 8, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_jump", L"images/enemy_schoolboy/SchoolBoyJump.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_jumpAttack", L"images/enemy_schoolboy/SchoolBoyJumpPunch.png", 6, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_groundDown", L"images/enemy_schoolboy/SchoolBoyKcockDown.png", 33, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_run", L"images/enemy_schoolboy/SchoolBoyRun.png", 10, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_skill", L"images/enemy_schoolboy/SchoolBoySandToss.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_stun", L"images/enemy_schoolboy/SchoolBoyStun.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_walk", L"images/enemy_schoolboy/SchoolBoyWalk.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_runAttack", L"images/enemy_schoolboy/SchoolDashAttack.png", 7, 2);
	// ** schoolGirl
	IMAGE_MANAGER->addFrameImage("schoolgirl_groundDown", L"images/enemy_schoolgirl/blowBack.png", 33, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_gethit", L"images/enemy_schoolgirl/getHit.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_heldHit", L"images/enemy_schoolgirl/HeldHit.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_heldRelease", L"images/enemy_schoolgirl/잡기 풀기.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_idle", L"images/enemy_schoolgirl/Idle.png", 10, 2);	
	IMAGE_MANAGER->addFrameImage("schoolgirl_stun", L"images/enemy_schoolgirl/stun.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_walk", L"images/enemy_schoolgirl/Walk.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_run", L"images/enemy_schoolgirl/run.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_block", L"images/enemy_schoolgirl/가드.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_groundHit", L"images/enemy_schoolgirl/그라운드 히트.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_attack1", L"images/enemy_schoolgirl/잽.png", 8, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_attack2", L"images/enemy_schoolgirl/니킥.png", 7, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_attack3", L"images/enemy_schoolgirl/발차기.png", 8, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_skill", L"images/enemy_schoolgirl/회전킥.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_jump", L"images/enemy_schoolgirl/점프.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_begGing", L"images/enemy_schoolgirl/항복.png", 3, 2);
	// ** 치어걸
	IMAGE_MANAGER->addFrameImage("cheergirl_block", L"images/enemy_cheergirl/block.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_groundHit", L"images/enemy_cheergirl/groundhit.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_idle", L"images/enemy_cheergirl/idle.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_attack1", L"images/enemy_cheergirl/japAttack.png", 6, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_jump", L"images/enemy_cheergirl/jump.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_run", L"images/enemy_cheergirl/run.png", 8, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_attack2", L"images/enemy_cheergirl/spinpoom.png", 7, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_begGing", L"images/enemy_cheergirl/begging.png", 2, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_blownBack", L"images/enemy_cheergirl/blownback.png", 23, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_skill", L"images/enemy_cheergirl/cartwheel.png", 15, 2); // 치어걸은 회피스킬
	IMAGE_MANAGER->addFrameImage("cheergirl_getHits", L"images/enemy_cheergirl/gethits.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_heldRelease", L"images/enemy_cheergirl/grab_release.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_groundUp", L"images/enemy_cheergirl/groundup.png", 11, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_stun", L"images/enemy_cheergirl/stun.png", 5, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_walk", L"images/enemy_cheergirl/walk.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_jumpAttack1", L"images/enemy_cheergirl/divekick_start.png", 6, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_jumpAttack2", L"images/enemy_cheergirl/divekick_middle.png", 7, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_jumpAttack3", L"images/enemy_cheergirl/divekick_end.png", 13, 2);

	// * 스테이지
	// ** 스테이지 배경 이미지 추가
	IMAGE_MANAGER->addImage("STAGE_1", L"resources/images/stages/stage_1.png");
	IMAGE_MANAGER->addImage("STAGE_2", L"resources/images/stages/stage_2.png");
	IMAGE_MANAGER->addImage("STAGE_BOSS_BEFORE", L"resources/images/stages/stage_boss_before.png");
	IMAGE_MANAGER->addImage("STAGE_BOSS_AFTER", L"resources/images/stages/stage_boss_after.png");
	IMAGE_MANAGER->addImage("screenBorder", L"resources/images/UI/playBorder.png");				// 플레이화면 테두리


	// * UI
	IMAGE_MANAGER->addImage("blackScreen", L"resources/images/UI/blackScreen.png");				// 검은 화면입니다.

	IMAGE_MANAGER->addImage("playerHPBackBar", L"resources/images/UI/kyoko_HP_backFrame.png");	// 플레이어 체력 뒤
	IMAGE_MANAGER->addImage("playerDigit"	 , L"resources/images/UI/kyoko_hp_digit.png");		// 플레이어 체력 앞
	IMAGE_MANAGER->addImage("playerHpFrame"	 , L"resources/images/UI/kyoko_frontFrame.png");	// 플레이어 체력 프레임	
	IMAGE_MANAGER->addImage("bossBackBar"	, L"resources/images/UI/boss_HP_backBar.png");		// 보스 체력 뒤
	IMAGE_MANAGER->addImage("bossFrontBar"	, L"resources/images/UI/boss_HP_frontBar.png");		// 보스 체력 앞
	IMAGE_MANAGER->addImage("bossHpFrame"	, L"resources/images/UI/boss_HP_frame.png");		// 보스 체력 프레임

	IMAGE_MANAGER->addImage("startMapPhone", L"resources/images/UI/startStage_phone.png");		// 핸드폰 이미지

	IMAGE_MANAGER->addImage("unlockDoor", L"resources/images/UI/door_unlock.png");			// 열린 문
	IMAGE_MANAGER->addImage("lockDoor"	, L"resources/images/UI/door_lock.png");			// 닫힌 문

	// * DIALOGUE
	string file;
	wstring fileW = L"";	
	for (int i = 1; i <= 6; i++)
	{
		// 쿄코
		if (i <= 5)
		{
			file = "resources/images/UI/dialogue/Kyoko_" + to_string(i) + ".png";
			fileW = L"";
			fileW.assign(file.begin(), file.end());
			IMAGE_MANAGER->addImage("kyoko_" + to_string(i), fileW);
		}
		// 미사코
		file = "resources/images/UI/dialogue/Misako_" + to_string(i) + ".png";
		fileW = L"";
		fileW.assign(file.begin(), file.end());
		IMAGE_MANAGER->addImage("misako_" + to_string(i), fileW);

		// 미스즈
		file = "resources/images/UI/dialogue/Misuzu_" + to_string(i) + ".png";
		fileW = L"";
		fileW.assign(file.begin(), file.end());
		IMAGE_MANAGER->addImage("misuzu_" + to_string(i), fileW);
	}

	D2D_RENDERER->addTextFormat(L"메이플스토리");		// 폰트 갖고옴	
	
	// 모든 씬 SCENE_MANAGER에 등록
	SCENE_MANAGER->addScene("MAIN", new MainScene);
	SCENE_MANAGER->addScene("STAGE", new StageScene);
	SCENE_MANAGER->changeScene("STAGE");	


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

	
}

//그리기 전용
void playGround::render()
{	
	//백버퍼 초기화
	D2D_RENDERER->beginRender(D2D1::ColorF::Black);
	{
		// _kyoko->render();
		SCENE_MANAGER->render();		
	}
	//백버퍼에 그린 내용들을 화면에 뿌려라~
	D2D_RENDERER->endRender();
}
