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
	Image*	portrait;	// 캐릭터 이미지
	Image*	name;		// 캐릭터 대화창 옆에 나올 이름
	Vector2 pos;		// 출력할 포지션
	Vector2 target;		// 목표 지점	
};

struct tagSkip
{
	ProgressBar* bar;	// 프로그레스 바
	float curGauge;		// 현재 게이지
	float maxGauge;		// 최대 게이지
	bool istayDown;		// 현재 누르고 있는 중
};

class DialogueManager
{
private:	
	queue<string>			_qCharacterMsg;	// 대사 저장
	queue<tagDialogueImg>	_qCharacterImg;	// 이미지 등 잡다한 것 저장
	tagSkip					_skip;			// 스킵 관련
	string					_writeText;		// 최종 출력할 텍스트
	bool					_isPlay;		// 현재 대화 진행중	
	float					_speed;			// 이미지 속도
	float					_textSpeed;		// 출력할 텍스트 속도
	float					_elapsedSec;	// 시간 계산용
	int						_stringNum;		// 출력할 글자 위치

	enum class curDialogue
	{
		ENTER,	// 이미지를 화면 안으로 가져와라
		WRITE,	// 대사를 출력해라
		EXIT,	// 이미지를 화면 밖으로 빼내라		
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


	// string >> wstring 한글 안깨짐
	wstring strTowstr(string src);
	bool textUpdate(float elapsedTime);
	bool findNameImg(string src, string name);
	void keyReaction();
};

