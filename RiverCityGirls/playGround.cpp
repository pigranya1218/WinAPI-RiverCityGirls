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

//�ʱ�ȭ �Լ�
HRESULT playGround::init()
{
	gameNode::init(true);

	//Enemy �̹��� 
	//*������
	ImageManager::GetInstance()->AddFrameImage("������_����1", L"images/enemy_schoolboy/SchoolBoyAttack1.png", 7, 2);
	ImageManager::GetInstance()->AddFrameImage("������_����2", L"images/enemy_schoolboy/SchoolBoyAttack2.png", 7, 2);
	ImageManager::GetInstance()->AddFrameImage("������_����3", L"images/enemy_schoolboy/SchoolBoyAttack3.png", 9, 2);
	ImageManager::GetInstance()->AddFrameImage("������_�׺�", L"images/enemy_schoolboy/SchoolBoybegging.png", 2, 2);
	ImageManager::GetInstance()->AddFrameImage("������_����", L"images/enemy_schoolboy/SchoolBoyBlock.png", 3, 2);
	ImageManager::GetInstance()->AddFrameImage("������_�ǰ�", L"images/enemy_schoolboy/SchoolBoyGetHit.png", 9, 2);
	ImageManager::GetInstance()->AddFrameImage("������_�׶����ǰ�", L"images/enemy_schoolboy/SchoolBoyGroundHit.png", 3, 2);
	ImageManager::GetInstance()->AddFrameImage("������_�ӹ��ǰ�", L"images/enemy_schoolboy/SchoolBoyHeldHit.png", 4, 2);
	ImageManager::GetInstance()->AddFrameImage("������_�ӹ�����", L"images/enemy_schoolboy/SchoolBoyHeldRelease.png", 4, 2);
	ImageManager::GetInstance()->AddFrameImage("������_�⺻", L"images/enemy_schoolboy/SchoolBoyIdle.png", 8, 2);
	ImageManager::GetInstance()->AddFrameImage("������_����", L"images/enemy_schoolboy/SchoolBoyJump.png", 3, 2);
	ImageManager::GetInstance()->AddFrameImage("������_��������", L"images/enemy_schoolboy/SchoolBoyJumpPunch.png", 6, 2);
	ImageManager::GetInstance()->AddFrameImage("������_�ٿ�", L"images/enemy_schoolboy/SchoolBoyKcockDown.png", 33, 2);
	ImageManager::GetInstance()->AddFrameImage("������_�޸���", L"images/enemy_schoolboy/SchoolBoyRun.png", 10, 2);
	ImageManager::GetInstance()->AddFrameImage("������_�𷡻Ѹ���", L"images/enemy_schoolboy/SchoolBoySandToss.png", 9, 2);
	ImageManager::GetInstance()->AddFrameImage("������_����", L"images/enemy_schoolboy/SchoolBoyStun.png", 4, 2);
	ImageManager::GetInstance()->AddFrameImage("������_�ȱ�", L"images/enemy_schoolboy/SchoolBoyWalk.png", 12, 2);
	ImageManager::GetInstance()->AddFrameImage("������_��ð���", L"images/enemy_schoolboy/SchoolDashAttack.png", 7, 2);
	//*�����
	ImageManager::GetInstance()->AddFrameImage("�����_�ǰ�_�ٿ�", L"images/enemy_schoolgirl/blowBack.png", 33, 2);
	ImageManager::GetInstance()->AddFrameImage("�����_�ǰ�", L"images/enemy_schoolgirl/getHit.png", 9, 2);
	ImageManager::GetInstance()->AddFrameImage("�����_�ӹ��ǰ�", L"images/enemy_schoolgirl/HeldHit.png", 4, 2);
	ImageManager::GetInstance()->AddFrameImage("�����_�ӹ�����", L"images/enemy_schoolgirl/��� Ǯ��.png", 4, 2);
	ImageManager::GetInstance()->AddFrameImage("�����_�⺻", L"images/enemy_schoolgirl/Idle.png", 10, 2);
	ImageManager::GetInstance()->AddFrameImage("�����_�ٿ�", L"images/enemy_schoolgirl/knokBack.png", 33, 2);
	ImageManager::GetInstance()->AddFrameImage("�����_����", L"images/enemy_schoolgirl/stun.png", 4, 2);
	ImageManager::GetInstance()->AddFrameImage("�����_�ȱ�", L"images/enemy_schoolgirl/Walk.png", 12, 2);
	ImageManager::GetInstance()->AddFrameImage("�����_�޸���", L"images/enemy_schoolgirl/run.png", 9, 2);
	ImageManager::GetInstance()->AddFrameImage("�����_����", L"images/enemy_schoolgirl/����.png", 3, 2);
	ImageManager::GetInstance()->AddFrameImage("�����_�׶����ǰ�", L"images/enemy_schoolgirl/�׶��� ��Ʈ.png", 3, 2);
	ImageManager::GetInstance()->AddFrameImage("�����_����1", L"images/enemy_schoolgirl/��.png", 8, 2);
	ImageManager::GetInstance()->AddFrameImage("�����_����2", L"images/enemy_schoolgirl/��ű.png", 7, 2);
	ImageManager::GetInstance()->AddFrameImage("�����_����3", L"images/enemy_schoolgirl/������.png", 8, 2);
	ImageManager::GetInstance()->AddFrameImage("�����_ȸ��ű", L"images/enemy_schoolgirl/ȸ��ű.png", 12, 2);
	ImageManager::GetInstance()->AddFrameImage("�����_����", L"images/enemy_schoolgirl/����.png", 3, 2);
	ImageManager::GetInstance()->AddFrameImage("�����_�׺�", L"images/enemy_schoolgirl/�׺�.png", 3, 2);


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

//�޸� ����
void playGround::release()
{
	OBJECTMANAGER->Release();
}

//����
void playGround::update()
{
	gameNode::update();
	OBJECTMANAGER->Update();
	EventManager::GetInstance()->Update();
	_enemyMg->update();
}

//�׸��� ����
void playGround::render()
{	
	//����� �ʱ�ȭ
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
		//////���Ĵ� 0~1������ ������ 0�� �Ⱥ��̴°Ű� 1�� ���������� ����
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
	//����ۿ� �׸� ������� ȭ�鿡 �ѷ���~
	D2DRenderer::GetInstance()->endRender();
}
