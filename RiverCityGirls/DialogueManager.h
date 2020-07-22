#pragma once
#include <fstream>
#include <queue>
#include <atlconv.h>
#include "ProgressBar.h"

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

struct tagSkip
{
	ProgressBar* bar;	// ���α׷��� ��
	float curGauge;		// ���� ������
	float maxGauge;		// �ִ� ������
	bool istayDown;		// ���� ������ �ִ� ��
};

class DialogueManager
{
private:	
	queue<string>			_qCharacterMsg;	// ��� ����
	queue<tagDialogueImg>	_qCharacterImg;	// �̹��� �� ����� �� ����
	tagSkip					_skip;			// ��ŵ ����
	string					_writeText;		// ���� ����� �ؽ�Ʈ
	bool					_isPlay;		// ���� ��ȭ ������	
	float					_speed;			// �̹��� �ӵ�
	float					_textSpeed;		// ����� �ؽ�Ʈ �ӵ�
	float					_elapsedSec;	// �ð� ����
	int						_stringNum;		// ����� ���� ��ġ

	enum class curDialogue
	{
		ENTER,	// �̹����� ȭ�� ������ �����Ͷ�
		WRITE,	// ��縦 ����ض�
		EXIT,	// �̹����� ȭ�� ������ ������		
	};
	curDialogue _curDialog;

public:
	DialogueManager();
	~DialogueManager();

	HRESULT init(float textSpeed);
	void release();
	void update();
	void render();

	void startChapter(BossChapter chapter);
	bool getIsPlay() { return _isPlay; }	


	// string >> wstring �ѱ� �ȱ���
	wstring strTowstr(string src);
	bool textUpdate(float elapsedTime);
	bool findNameImg(string src, string name);
	void keyReaction();
};

