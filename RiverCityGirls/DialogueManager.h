#pragma once
#include <fstream>

enum class BossChapter
{
	BATTLE_BEFORE,
	BATTLE_AFTER
};

class DialogueManager
{
private:
	vector<string>	_msg;
	vector<Image*>	_img;
	BossChapter		_curChapter;
	string			_rendText;

	bool			_isPlay;

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

