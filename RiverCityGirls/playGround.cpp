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

	ImageManager::GetInstance()->AddImage("TestObject", L"TrapObject.png");
	ImageManager::GetInstance()->AddFrameImage("TestFrameObject",
		L"Bomb.png", 3, 1);

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
}

//그리기 전용
void playGround::render()
{	
	//백버퍼 초기화
	D2DRenderer::GetInstance()->BeginRender(D2D1::ColorF::Black);
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
	}
	//백버퍼에 그린 내용들을 화면에 뿌려라~
	D2DRenderer::GetInstance()->EndRender();
}
