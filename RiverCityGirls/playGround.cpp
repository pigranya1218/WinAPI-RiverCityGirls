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

	IMAGE_MANAGER->addFrameImage("Kyoko_idle", L"Kyoko/Kyoko_idle.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_walk", L"Kyoko/Kyoko_walk.png",12,2);
	IMAGE_MANAGER->addFrameImage("Kyoko_run", L"Kyoko/Kyoko_run.png", 16, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_jump", L"Kyoko/Kyoko_jump.png", 3, 2);

	//Enemy �̹��� 
    //������
	IMAGE_MANAGER->addFrameImage("������_����1", L"images/enemy_schoolboy/SchoolBoyAttack1.png", 7, 2);
	IMAGE_MANAGER->addFrameImage("������_����2", L"images/enemy_schoolboy/SchoolBoyAttack2.png", 7, 2);
	IMAGE_MANAGER->addFrameImage("������_����3", L"images/enemy_schoolboy/SchoolBoyAttack3.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("������_�׺�", L"images/enemy_schoolboy/SchoolBoybegging.png", 2, 2);
	IMAGE_MANAGER->addFrameImage("������_����", L"images/enemy_schoolboy/SchoolBoyBlock.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("������_�ǰ�", L"images/enemy_schoolboy/SchoolBoyGetHit.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("������_�׶����ǰ�", L"images/enemy_schoolboy/SchoolBoyGroundHit.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("������_�ӹ��ǰ�", L"images/enemy_schoolboy/SchoolBoyHeldHit.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("������_�ӹ�����", L"images/enemy_schoolboy/SchoolBoyHeldRelease.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("������_�⺻", L"images/enemy_schoolboy/SchoolBoyIdle.png", 8, 2);
	IMAGE_MANAGER->addFrameImage("������_����", L"images/enemy_schoolboy/SchoolBoyJump.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("������_��������", L"images/enemy_schoolboy/SchoolBoyJumpPunch.png", 6, 2);
	IMAGE_MANAGER->addFrameImage("������_�ٿ�", L"images/enemy_schoolboy/SchoolBoyKcockDown.png", 33, 2);
	IMAGE_MANAGER->addFrameImage("������_�޸���", L"images/enemy_schoolboy/SchoolBoyRun.png", 10, 2);
	IMAGE_MANAGER->addFrameImage("������_�𷡻Ѹ���", L"images/enemy_schoolboy/SchoolBoySandToss.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("������_����", L"images/enemy_schoolboy/SchoolBoyStun.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("������_�ȱ�", L"images/enemy_schoolboy/SchoolBoyWalk.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("������_��ð���", L"images/enemy_schoolboy/SchoolDashAttack.png", 7, 2);
	//�����
	IMAGE_MANAGER->addFrameImage("�����_�ǰ�_�ٿ�", L"images/enemy_schoolgirl/blowBack.png", 33, 2);
	IMAGE_MANAGER->addFrameImage("�����_�ǰ�", L"images/enemy_schoolgirl/getHit.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("�����_�ӹ��ǰ�", L"images/enemy_schoolgirl/HeldHit.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("�����_�ӹ�����", L"images/enemy_schoolgirl/��� Ǯ��.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("�����_�⺻", L"images/enemy_schoolgirl/Idle.png", 10, 2);
	IMAGE_MANAGER->addFrameImage("�����_�ٿ�", L"images/enemy_schoolgirl/knokBack.png", 33, 2);
	IMAGE_MANAGER->addFrameImage("�����_����", L"images/enemy_schoolgirl/stun.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("�����_�ȱ�", L"images/enemy_schoolgirl/Walk.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("�����_�޸���", L"images/enemy_schoolgirl/run.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("�����_����", L"images/enemy_schoolgirl/����.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("�����_�׶����ǰ�", L"images/enemy_schoolgirl/�׶��� ��Ʈ.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("�����_����1", L"images/enemy_schoolgirl/��.png", 8, 2);
	IMAGE_MANAGER->addFrameImage("�����_����2", L"images/enemy_schoolgirl/��ű.png", 7, 2);
	IMAGE_MANAGER->addFrameImage("�����_����3", L"images/enemy_schoolgirl/������.png", 8, 2);
	IMAGE_MANAGER->addFrameImage("�����_ȸ��ű", L"images/enemy_schoolgirl/ȸ��ű.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("�����_����", L"images/enemy_schoolgirl/����.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("�����_�׺�", L"images/enemy_schoolgirl/�׺�.png", 3, 2);


	/*_enemyMg = new enemyManager;
	_enemyMg->init();*/
	// ��� �̹��� IMAGE_MANAGER�� ���
	// * ��������
	// ** �������� ��� �̹��� �߰�
	IMAGE_MANAGER->addImage("STAGE_1", L"resources/images/stages/stage_1.png");
	IMAGE_MANAGER->addImage("STAGE_2", L"resources/images/stages/stage_2.png");
	IMAGE_MANAGER->addImage("STAGE_BOSS_BEFORE", L"resources/images/stages/stage_boss_before.png");
	IMAGE_MANAGER->addImage("STAGE_BOSS_AFTER", L"resources/images/stages/stage_boss_after.png");
	IMAGE_MANAGER->addImage("screenBorder", L"resources/images/UI/playBorder.png");				// �÷���ȭ�� �׵θ�


	// UI �̹����Դϴ�.
	IMAGE_MANAGER->addImage("blackScreen", L"resources/images/UI/blackScreen.png");				// ���� ȭ���Դϴ�.

	IMAGE_MANAGER->addImage("playerHPBackBar", L"resources/images/UI/kyoko_HP_backFrame.png");	// �÷��̾� ü�� ��
	IMAGE_MANAGER->addImage("playerDigit"	 , L"resources/images/UI/kyoko_hp_digit.png");		// �÷��̾� ü�� ��
	IMAGE_MANAGER->addImage("playerHpFrame"	 , L"resources/images/UI/kyoko_frontFrame.png");	// �÷��̾� ü�� ������	
	IMAGE_MANAGER->addImage("bossBackBar"	, L"resources/images/UI/boss_HP_backBar.png");		// ���� ü�� ��
	IMAGE_MANAGER->addImage("bossFrontBar"	, L"resources/images/UI/boss_HP_frontBar.png");		// ���� ü�� ��
	IMAGE_MANAGER->addImage("bossHpFrame"	, L"resources/images/UI/boss_HP_frame.png");		// ���� ü�� ������

	IMAGE_MANAGER->addImage("startMapPhone", L"resources/images/UI/startStage_phone.png");		// �ڵ��� �̹���

	IMAGE_MANAGER->addImage("unlockDoor", L"resources/images/UI/door_unlock.png");			// ���� ��
	IMAGE_MANAGER->addImage("lockDoor"	, L"resources/images/UI/door_lock.png");			// ���� ��

	// ���̾�α� �̹����Դϴ�.
	string file;
	wstring fileW = L"";	
	for (int i = 1; i <= 6; i++)
	{
		// ����
		if (i <= 5)
		{
			file = "resources/images/UI/dialogue/Kyoko_" + to_string(i) + ".png";
			fileW = L"";
			fileW.assign(file.begin(), file.end());
			IMAGE_MANAGER->addImage("kyoko_" + to_string(i), fileW);
		}
		// �̻���
		file = "resources/images/UI/dialogue/Misako_" + to_string(i) + ".png";
		fileW = L"";
		fileW.assign(file.begin(), file.end());
		IMAGE_MANAGER->addImage("misako_" + to_string(i), fileW);

		// �̽���
		file = "resources/images/UI/dialogue/Misuzu_" + to_string(i) + ".png";
		fileW = L"";
		fileW.assign(file.begin(), file.end());
		IMAGE_MANAGER->addImage("misuzu_" + to_string(i), fileW);
	}

	D2D_RENDERER->addTextFormat(L"�����ý��丮");		// ��Ʈ �����	
	
	// ��� �� SCENE_MANAGER�� ���
	SCENE_MANAGER->addScene("MAIN", new MainScene);
	SCENE_MANAGER->addScene("STAGE", new StageScene);
	SCENE_MANAGER->changeScene("STAGE");	


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
	D2D_RENDERER->beginRender(D2D1::ColorF::Black);
	{
		// _kyoko->render();
		SCENE_MANAGER->render();		
	}
	//����ۿ� �׸� ������� ȭ�鿡 �ѷ���~
	D2D_RENDERER->endRender();
}
