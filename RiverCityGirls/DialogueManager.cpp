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
	_writeText = L"";
	_speed = 30.0f;	
	_isPlay = _stringNum = 0;

	return S_OK;
}

void DialogueManager::release()
{
}

void DialogueManager::update()
{
	if (!_isPlay) return;

	switch (_curDialog)
	{
		case DialogueManager::curDialogue::ENTER:
		{
			Vector2& pos = _qCharacterImg.front().pos;			
			if (getDistance(pos.x, pos.y, _qCharacterImg.front().target.x, _qCharacterImg.front().target.y) > _speed)
			{
				float angle = getAngle(pos.x, pos.y, _qCharacterImg.front().target.x, _qCharacterImg.front().target.y);				

				pos.x += cosf(angle) * _speed;
				pos.y -= sinf(angle) * _speed;
				
			}
			else
			{
				pos = _qCharacterImg.front().target;
				_curDialog = curDialogue::WRITE;
			}
			break;
		}		
		case DialogueManager::curDialogue::WRITE:
		{
			
			
			_writeText.assign(_qCharacterMsg.front().begin(), _qCharacterMsg.front().end());

			_curDialog = curDialogue::EXIT;
			break;
		}
		
		case DialogueManager::curDialogue::EXIT:
		{
			break;
		}		
	}
}

void DialogueManager::render()
{
	if (!_isPlay) return;
	// 폰트 테스트용
	//D2D_RENDERER->renderText(WINSIZEX / 2 - 300, WINSIZEY / 2, L"호로로로ㅗ로록!!", 100, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_CENTER, L"메이플스토리");

	_qCharacterImg.front().portrait->setScale(0.8f);
	_qCharacterImg.front().portrait->render(_qCharacterImg.front().pos);
	//_writeText = L"안녕";
	D2D_RENDERER->renderText(WINSIZEX / 2 + 200, WINSIZEY / 2, _writeText, 50, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_CENTER);
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

			tagDialogueImg characterImg;
			ZeroMemory(&characterImg, sizeof(characterImg));
			
			characterImg.portrait = IMAGE_MANAGER->findImage(str.substr(0, atPos));

			if (str.find("Misuzu") == string::npos)
			{
				characterImg.target = Vector2((float)characterImg.portrait->getWidth() / 1.5f, (float)(WINSIZEY - characterImg.portrait->getHeight() / 2));
				characterImg.pos = Vector2(0.0f - characterImg.portrait->getWidth() / 2, characterImg.target.y);
			}
			else
			{
				characterImg.target = Vector2((float)(WINSIZEX - characterImg.portrait->getWidth() / 1.5f), (float)(WINSIZEY - characterImg.portrait->getHeight() / 2));
				characterImg.pos = Vector2((float)(WINSIZEX + characterImg.portrait->getWidth() / 2), characterImg.target.y);
			}						
			
			string characterMsg = "안녕!";

			_qCharacterImg.push(characterImg);
			_qCharacterMsg.push(characterMsg);
			
		}
	}
	readMsg.close();

	_isPlay = true;

	_curDialog = curDialogue::ENTER;
}
