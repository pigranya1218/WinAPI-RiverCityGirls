#include "stdafx.h"
#include "DialogueManager.h"

DialogueManager::DialogueManager()
{
}

DialogueManager::~DialogueManager()
{
}

HRESULT DialogueManager::init()
{
	




	_isPlay = false;

	return S_OK;
}

void DialogueManager::release()
{
}

void DialogueManager::update()
{
	if (!_isPlay) return;
	


}

void DialogueManager::render()
{
	if (!_isPlay) return;
	// 폰트 테스트용
	D2D_RENDERER->renderText(WINSIZEX / 2 - 300, WINSIZEY / 2, L"호로로로ㅗ로록!!", 100, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_CENTER, L"메이플스토리");

	for (int i = 0; i < _img.size(); i++)
	{
		_img[i]->setAlpha(0.5f);
		_img[i]->render(Vector2(WINSIZEX / 2, WINSIZEY / 2));
	}
}

void DialogueManager::startChapter(BossChapter chapter)
{
	if (_isPlay) return;

	string filePath = "resources/dialogue/";
	string fileName;

	switch (chapter)
	{
		case BossChapter::BATTLE_BEFORE:
		{
			fileName = filePath + "boss_start.txt";
			break;
		}		
		case BossChapter::BATTLE_AFTER:
		{
			fileName = filePath + "boss_finish.txt";
			break;
		}
	}

	ifstream readMsg;
	readMsg.open(fileName);

	string str;
	int atPos;
	if (readMsg.is_open())
	{
		while (!readMsg.eof())
		{			
			getline(readMsg, str);
			atPos = str.find('@', 0);

			Image* img = IMAGE_MANAGER->findImage(str.substr(0, atPos));
			string msg = str.substr(atPos + 1, str.size() - 1);

			_img.push_back(img);
			_msg.push_back(msg);
		}
	}

	_isPlay = true;
}
