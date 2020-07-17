#include "stdafx.h"
#include "PlayGround.h"
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

//�ʱ�ȭ �Լ�
HRESULT playGround::init()
{
	GameNode::init(true);

	IMAGE_MANAGER->addImage("TestObject", L"TrapObject.png");
	IMAGE_MANAGER->addFrameImage("TestFrameObject",
		L"Bomb.png", 3, 1);

	Player* player = new Player();
	player->init();
	OBJECT_MANAGER->addObject(ObjectType::Player, player);

	EventManager::getInstance()->addEvent(new IObjectMove
	(
		player, Vector2(WINSIZEX, WINSIZEY / 2), 100.f
	));

	EventManager::getInstance()->addEvent(new IObjectMove
	(
		player, Vector2(WINSIZEX / 2, WINSIZEY / 2), 100.f
	));

	return S_OK;
}

//�޸� ����
void playGround::release()
{
	OBJECT_MANAGER->release();
}

//����
void playGround::update()
{
	GameNode::update();
	OBJECT_MANAGER->update();
	EventManager::getInstance()->update();
}

//�׸��� ����
void playGround::render()
{	
	//����� �ʱ�ȭ
	D2DRenderer::GetInstance()->beginRender(D2D1::ColorF::Black);
	{
		OBJECT_MANAGER->render();
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
		//////���Ĵ� 0~1������ ������ 0�� �Ⱥ��̴°Ű� 1�� ���������� ����
		////image->SetAlpha(0.5f);
		//////image->SetSize(Vector2(100, 100));
		////image->Render(Vector2(WINSIZEX / 2, WINSIZEY / 2));
		//
		//Image* frameImage = ImageManager::GetInstance()->FindImage("TestFrameObject");
		//
		//frameImage->SetAlpha(0.3f);
		//frameImage->FrameRender(Vector2(WINSIZEX / 2, WINSIZEY / 2), 0, 0);
	}
	//����ۿ� �׸� ������� ȭ�鿡 �ѷ���~
	D2DRenderer::GetInstance()->endRender();
}
