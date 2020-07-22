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
	Image*	portrait;	// 캐릭터 이미지
	Image*	name;		// 캐릭터 대화창 옆에 나올 이름
	Vector2 pos;		// 출력할 포지션
	Vector2 target;		// 목표 지점	
};

class DialogueManager
{
private:
	queue<string>			_qCharacterMsg;	// 대사 저장
	queue<tagDialogueImg>	_qCharacterImg;	// 이미지 등 잡다한 것 저장

	wstring					_writeText;

	bool			_isPlay;
	float			_speed;
	int _stringNum;

	enum class curDialogue
	{
		ENTER,	// 이미지를 화면 안으로 가져와라
		WRITE,	// 대사를 출력해라
		EXIT	// 이미지를 화면 밖으로 빼내라
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

