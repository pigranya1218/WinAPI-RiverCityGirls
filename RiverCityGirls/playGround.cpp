#include "stdafx.h"
#include "playGround.h"
#include "Player.h"
#include "Obstacle.h"
#include "EventManager.h"
#include "IEvent.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화 함수
HRESULT playGround::init()
{
	gameNode::init(true);

	//Enemy 이미지 
	//*스쿨보이
	ImageManager::GetInstance()->AddFrameImage("스쿨보이_공격1", L"images/enemy_schoolboy/SchoolBoyAttack1.png", 7, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨보이_공격2", L"images/enemy_schoolboy/SchoolBoyAttack2.png", 7, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨보이_공격3", L"images/enemy_schoolboy/SchoolBoyAttack3.png", 9, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨보이_항복", L"images/enemy_schoolboy/SchoolBoybegging.png", 2, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨보이_가드", L"images/enemy_schoolboy/SchoolBoyBlock.png", 3, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨보이_피격", L"images/enemy_schoolboy/SchoolBoyGetHit.png", 9, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨보이_그라운드피격", L"images/enemy_schoolboy/SchoolBoyGroundHit.png", 3, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨보이_속박피격", L"images/enemy_schoolboy/SchoolBoyHeldHit.png", 4, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨보이_속박해제", L"images/enemy_schoolboy/SchoolBoyHeldRelease.png", 4, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨보이_기본", L"images/enemy_schoolboy/SchoolBoyIdle.png", 8, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨보이_점프", L"images/enemy_schoolboy/SchoolBoyJump.png", 3, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨보이_점프공격", L"images/enemy_schoolboy/SchoolBoyJumpPunch.png", 6, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨보이_다운", L"images/enemy_schoolboy/SchoolBoyKcockDown.png", 33, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨보이_달리기", L"images/enemy_schoolboy/SchoolBoyRun.png", 10, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨보이_모래뿌리기", L"images/enemy_schoolboy/SchoolBoySandToss.png", 9, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨보이_스턴", L"images/enemy_schoolboy/SchoolBoyStun.png", 4, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨보이_걷기", L"images/enemy_schoolboy/SchoolBoyWalk.png", 12, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨보이_대시공격", L"images/enemy_schoolboy/SchoolDashAttack.png", 7, 2);
	//*스쿨걸
	ImageManager::GetInstance()->AddFrameImage("스쿨걸_피격_다운", L"images/enemy_schoolgirl/blowBack.png", 33, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨걸_피격", L"images/enemy_schoolgirl/getHit.png", 9, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨걸_속박피격", L"images/enemy_schoolgirl/HeldHit.png", 4, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨걸_속박해제", L"images/enemy_schoolgirl/잡기 풀기.png", 4, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨걸_기본", L"images/enemy_schoolgirl/Idle.png", 10, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨걸_다운", L"images/enemy_schoolgirl/knokBack.png", 33, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨걸_스턴", L"images/enemy_schoolgirl/stun.png", 4, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨걸_걷기", L"images/enemy_schoolgirl/Walk.png", 12, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨걸_달리기", L"images/enemy_schoolgirl/run.png", 9, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨걸_가드", L"images/enemy_schoolgirl/가드.png", 3, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨걸_그라운드피격", L"images/enemy_schoolgirl/그라운드 히트.png", 3, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨걸_공격1", L"images/enemy_schoolgirl/잽.png", 8, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨걸_공격2", L"images/enemy_schoolgirl/니킥.png", 7, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨걸_공격3", L"images/enemy_schoolgirl/발차기.png", 8, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨걸_회전킥", L"images/enemy_schoolgirl/회전킥.png", 12, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨걸_점프", L"images/enemy_schoolgirl/점프.png", 3, 2);
	ImageManager::GetInstance()->AddFrameImage("스쿨걸_항복", L"images/enemy_schoolgirl/항복.png", 3, 2);


	_enemyMg = new enemyManager;
	_enemyMg->init();

	Player* player = new Player();
	player->Init();
	OBJECTMANAGER->AddObject(ObjectType::Player, player);

	EventManager::GetInstance()->AddEvent(new IObjectMove
	(
		player, Vector2(WINSIZEX, WINSIZEY / 2), 100.f
	));

	EventManager::GetInstance()->AddEvent(new IObjectMove
	(
		player, Vector2(WINSIZEX / 2, WINSIZEY / 2), 100.f
	));

	return S_OK;
}

//메모리 해제
void playGround::release()
{
	OBJECTMANAGER->Release();
}

//연산
void playGround::update()
{
	gameNode::update();
	OBJECTMANAGER->Update();
	EventManager::GetInstance()->Update();
	_enemyMg->update();
}

//그리기 전용
void playGround::render()
{	
	//백버퍼 초기화
	D2DRenderer::GetInstance()->beginRender(D2D1::ColorF::White);
	{
		OBJECTMANAGER->Render();
		//FloatRect rect;
		//rect = RectMakePivot(Vector2(WINSIZEX / 2, WINSIZEY / 2),
		//	Vector2(50, 50), Pivot::Center);
		//
		//D2DRenderer::GetInstance()->DrawRectangle
		//(
		//	rect,
		//	D2DRenderer::DefaultBrush::Red,
		//	1.f
		//);
		//
		//D2DRenderer::GetInstance()->DrawEllipse
		//(
		//	Vector2(WINSIZEX / 2, WINSIZEY / 2), 
		//	50, 
		//	D2DRenderer::DefaultBrush::Red,
		//	1.f
		//);
		//
		//
		////Image* image = ImageManager::GetInstance()->FindImage("TestObject");
		////
		////image->SetAngle(30.f);
		//////알파는 0~1사이의 값으로 0은 안보이는거고 1은 반투명하지 않은
		////image->SetAlpha(0.5f);
		//////image->SetSize(Vector2(100, 100));
		////image->Render(Vector2(WINSIZEX / 2, WINSIZEY / 2));
		//
		//Image* frameImage = ImageManager::GetInstance()->FindImage("TestFrameObject");
		//
		//frameImage->SetAlpha(0.3f);
		//frameImage->FrameRender(Vector2(WINSIZEX / 2, WINSIZEY / 2), 0, 0);

		_enemyMg->render();
	}
	//백버퍼에 그린 내용들을 화면에 뿌려라~
	D2DRenderer::GetInstance()->endRender();
}
