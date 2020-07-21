#pragma once
#include <fstream>
#include <queue>

enum class BossChapter
{
	BATTLE_BEFORE,
	BATTLE_AFTER
};

struct tagDialogueImg
{
	Image*	portrait;	// ĳ���� �̹���
	Image*	name;		// ĳ���� ��ȭâ ���� ���� �̸�
	Vector2 pos;		// ����� ������
	Vector2 target;		// ��ǥ ����	
};

class DialogueManager
{
private:
	queue<string>			_qCharacterMsg;	// ��� ����
	queue<tagDialogueImg>	_qCharacterImg;	// �̹��� �� ����� �� ����

	wstring					_writeText;

	bool			_isPlay;
	float			_speed;
	int _stringNum;

	enum class curDialogue
	{
		ENTER,	// �̹����� ȭ�� ������ �����Ͷ�
		WRITE,	// ��縦 ����ض�
		EXIT	// �̹����� ȭ�� ������ ������
	};
	curDialogue _curDialog;


public:
	DialogueManager();
	~DialogueManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void startChapter(BossChapter chapter);
	bool getIsPlay() { return _isPlay; }
};

