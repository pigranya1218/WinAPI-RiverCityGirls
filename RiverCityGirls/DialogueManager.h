#pragma once
#include <fstream>
#include <queue>
#include "ProgressBar.h"

enum class BossChapter
{
	BATTLE_BEFORE,
	BATTLE_AFTER
};

struct tagDialogueImgInfo
{
	Image*	portrait;	// ĳ���� �̹���
	Image*	name;		// ĳ���� ��ȭâ ���� ���� �̸�
	Vector2 pos;		// ����� ������
	Vector2 target;		// ��ǥ ����	
};

struct tagSkipInfo
{
	ProgressBar* bar;	// ���α׷��� ��
	float curGauge;		// ���� ������
	float maxGauge;		// �ִ� ������
	bool istayDown;		// ���� ������ �ִ� ��
};

class Battle
{
private:


public:
	Battle() {}
	~Battle(){}
};

class DialogueManager
{
private:	
	queue<string>				_qCharacterMsg;	// ��� ����
	queue<tagDialogueImgInfo>	_qCharacterImg;	// �̹��� �� ����� �� ����
	tagSkipInfo					_skip;			// ��ŵ ����
	string						_writeText;		// ���� ����� �ؽ�Ʈ
	bool						_isPlay;		// ���� ��ȭ ������	
	float						_speed;			// �̹��� �ӵ�
	float						_textSpeed;		// ����� �ؽ�Ʈ �ӵ�
	float						_elapsedSec;	// �ð� ����
	int							_stringNum;		// ����� ���� ��ġ
	float						_textTerm;		// �ؽ�Ʈ ��� �Ϸ� �� ȭ�� �Ѿ �ӵ�
	float						_textY;			// �ؽ�Ʈ�� ���� ��  Y�� ��ġ ����	

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
	
	bool textUpdate(float elapsedTime);
	bool findNameImg(string src, string name);
	void keyReaction();
};

