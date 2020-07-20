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
	IMAGE_MANAGER->addImage("screenBorder", L"resources/images/UI/playBorder.png");					// �÷���ȭ�� �׵θ�

	IMAGE_MANAGER->addImage("playerBackBar"	, L"resources/images/UI/UI_Player_HP_BackBar.png");		// �÷��̾� ü�� ��
	IMAGE_MANAGER->addImage("playerFrontBar", L"resources/images/UI/UI_Player_HP_FrontBar.png");	// �÷��̾� ü�� ��
	IMAGE_MANAGER->addImage("playerHpFrame"	, L"resources/images/UI/UI_Player_Bar.png");			// �÷��̾� ü�� ������
	IMAGE_MANAGER->addImage("kyokoShot"		, L"resources/images/UI/UI_kyoko_shot.png");			// �÷��̾� ü�� �� �̹���

	IMAGE_MANAGER->addImage("bossBackBar"	, L"resources/images/UI/UI_Boss_HP_BackBar.png");		// ���� ü�� ��
	IMAGE_MANAGER->addImage("bossFrontBar"	, L"resources/images/UI/UI_Boss_HP_FrontBar.png");		// ���� ü�� ��
	IMAGE_MANAGER->addImage("bossHpFrame"	, L"resources/images/UI/UI_Boss_HP_Frame.png");			// ���� ü�� ������

	IMAGE_MANAGER->addImage("startMapPhone", L"resources/images/UI/startStage_phone.png");			// �ڵ��� �̹���

	
	
	IMAGE_MANAGER->addImage("unlockDoor", L"resources/images/UI/UI_UNLOCKED_DOOR.png");				// ���� ��
	IMAGE_MANAGER->addImage("lockDoor"	, L"resources/images/UI/UI_LOCKED_DOOR.png");				// ���� ��
	
	


	// ��� �� SCENE_MANAGER�� ���
	SCENE_MANAGER->addScene("MAIN", new MainScene);
	SCENE_MANAGER->addScene("STAGE", new StageScene);
	SCENE_MANAGER->changeScene("STAGE");

	// UI �׽�Ʈ��
	UI_MANAGER->init();
	UI_MANAGER->setBossHpActive(true);
	UI_MANAGER->setPlayerHp(100.0f, 100.0f);
	UI_MANAGER->setPlayerHpActive(true);
	UI_MANAGER->setBossHp(100.0f, 100.0f);

	UI_MANAGER->setDoorLock(true, Vector2(WINSIZEX / 2, WINSIZEY / 2), currentDoor::UNLOCK, 0.5f);


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
	UI_MANAGER->update();

	static float hp = 100;
	if (hp < 0) hp = 100;
	hp -= 0.5f;
	UI_MANAGER->setBossHp(hp, 100.0f);	
	UI_MANAGER->setPlayerHp(hp, 100.0f);
}

//�׸��� ����
void playGround::render()
{	
	//����� �ʱ�ȭ
	D2D_RENDERER->beginRender(D2D1::ColorF::Black);
	{
		SCENE_MANAGER->render();
		UI_MANAGER->render();		

	}
	//����ۿ� �׸� ������� ȭ�鿡 �ѷ���~
	D2D_RENDERER->endRender();
}
