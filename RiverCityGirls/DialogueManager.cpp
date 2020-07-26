#include "stdafx.h"
#include "DialogueManager.h"
#include <string>


DialogueManager::DialogueManager()
{
}

DialogueManager::~DialogueManager()
{
}

HRESULT DialogueManager::init(float textSpeed)
{
	ZeroMemory(&_skip, sizeof(_skip));
	Vector2 skipPos = IMAGE_MANAGER->findImage("skipBack")->getSize();
	_skip.bar = new ProgressBar;
	_skip.bar->init("skipBack", "skipFront", Vector2(WINSIZEX - skipPos.x / 2, skipPos.y / 2));	// ��ŵ�� �̹���, ��ǥ ����
	_skip.maxGauge = 100;

	_textSpeed = 1.0f / textSpeed;	// ��ȭ ��� �ӵ�
	_writeText.clear();				// ��Ʈ�� �ʱ�ȭ
	_speed = 30.0f;					// �̹��� ������ �ӵ�
	_textTerm = 2.5f;
	_isPlay = _stringNum = _elapsedSec = 0;

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
		case DialogueManager::curDialogue::ENTER:	// �̹��� ȭ�� ������ ������
		{
			Vector2& pos = _qCharacterImg.front().pos;

			_textY = WINSIZEY - _qCharacterImg.front().name->getHeight() * 2.0f;

			if (KEY_MANAGER->isOnceKeyDown(VK_SPACE))
			{
				pos = _qCharacterImg.front().target;				
			}
			if (getDistance(pos.x, pos.y, _qCharacterImg.front().target.x, _qCharacterImg.front().target.y) > _speed)
			{
				float angle = getAngle(pos.x, pos.y, _qCharacterImg.front().target.x, _qCharacterImg.front().target.y);				
				pos.x += cosf(angle) * _speed;									
			}
			else
			{
				pos = _qCharacterImg.front().target;
				_textTerm = 2.5f;	// �ӵ��� �׻� �⺻ ������ �ʱ�ȭ
				_curDialog = curDialogue::WRITE;
			}
			break;
		}		
		case DialogueManager::curDialogue::WRITE:	// ��ȭ ���
		{			
			if (KEY_MANAGER->isOnceKeyDown(VK_SPACE))
			{
				_writeText = _qCharacterMsg.front();
				_stringNum = _qCharacterMsg.front().length();
				_textTerm = 0.8f;	// �ڵ� �ϼ� �� �ӵ��� �ణ ������
				if (_writeText.find("\n") != string::npos)
				{
					_textY = WINSIZEY - _qCharacterImg.front().name->getHeight() * 2.0f - 20;
				}
			}			
			if (_stringNum < _qCharacterMsg.front().length())
			{				
				if (textUpdate(TIME_MANAGER->getElapsedTime() * 10))
				{
					// �ѱ��� �ƽ�Ű ���� ������ ����
					if (static_cast<int>(_qCharacterMsg.front().at(_stringNum)) < 0)
					{
						// �ѱ��� 2����Ʈ �����̱⿡ 2���� �� ���� ������
						for (int i = 0; i < 2; i++)
						{
							_writeText.push_back(_qCharacterMsg.front().at(_stringNum++));
						}						
					}
					else
					{
						if (_qCharacterMsg.front().substr(_stringNum, 1) == "\n")
						{
							_textY = WINSIZEY - _qCharacterImg.front().name->getHeight() * 2.0f - 20;
						}
						_writeText.push_back(_qCharacterMsg.front().at(_stringNum++));
					}					
				}						
			}			
			else
			{
				if (textUpdate(TIME_MANAGER->getElapsedTime() * _textTerm))
				{
					_curDialog = curDialogue::EXIT;
					_stringNum = 0;
					_writeText.clear();
				}
			}
			break;
		}		
		case DialogueManager::curDialogue::EXIT:	// �̹����� ȭ�� �ٱ����� �о
		{						
			Vector2& pos = _qCharacterImg.front().pos;

			// �ٽ� ȭ�� ������ ���� ��ǥ
			_qCharacterImg.front().target = (pos.x < WINSIZEX / 2) ?
				Vector2(0.0f - _qCharacterImg.front().portrait->getWidth() / 1.5f, pos.y) : 
				Vector2(WINSIZEX + _qCharacterImg.front().portrait->getWidth() / 1.5f, pos.y);

			if (KEY_MANAGER->isOnceKeyDown(VK_SPACE))
			{
				pos = _qCharacterImg.front().target;
			}
			if (getDistance(pos.x, pos.y, _qCharacterImg.front().target.x, _qCharacterImg.front().target.y) > _speed)
			{
				float angle = getAngle(pos.x, pos.y, _qCharacterImg.front().target.x, _qCharacterImg.front().target.y);
				pos.x += cosf(angle) * _speed;				
			}
			else
			{
				pos = _qCharacterImg.front().target;
				_curDialog = curDialogue::ENTER;

				_qCharacterImg.pop();
				_qCharacterMsg.pop();

				_stringNum = 0;

				if (_qCharacterImg.empty() && _qCharacterMsg.empty()) _isPlay = false;
			}				
			break;
		}
	}
	keyReaction();
}

void DialogueManager::render()
{
	if (!_isPlay) return;

	IMAGE_MANAGER->findImage("blackScreen")->setSize(Vector2(WINSIZEX, WINSIZEY));
	IMAGE_MANAGER->findImage("blackScreen")->setAlpha(0.5f);
	IMAGE_MANAGER->findImage("blackScreen")->render(Vector2(WINSIZEX / 2, WINSIZEY / 2));

	if (_skip.istayDown) 
	{
		_skip.bar->render();
	}

	_qCharacterImg.front().portrait->setScale(0.8f);
	_qCharacterImg.front().portrait->render(_qCharacterImg.front().pos);
	_qCharacterImg.front().name->render(Vector2(_qCharacterImg.front().name->getWidth() / 1.5f, WINSIZEY - _qCharacterImg.front().name->getHeight() * 1.5f));
	
	D2D_RENDERER->renderText(
		_qCharacterImg.front().name->getWidth() * 1.5f,						// X��
		_textY,																// Y��
		stringTOwsting(_writeText),											// string >> wstring ��ȯ
		30,																	// ��Ʈ ũ��
		D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING,	// ������ ��������
		L"�����ý��丮"														// ��Ʈ
	);
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
	
	if (readMsg.is_open())
	{
		while (!readMsg.eof())
		{			
			string str;
			int atPos;

			getline(readMsg, str);
			atPos = str.find('@', 0);					
			
			tagDialogueImgInfo characterImg;
			ZeroMemory(&characterImg, sizeof(characterImg));
			
			characterImg.portrait = IMAGE_MANAGER->findImage(str.substr(0, atPos));
			string keyName = findNameImg(str, "kyoko") ? "kyokoName" : findNameImg(str, "misako") ? "misakoName" : "misuzuName";
			characterImg.name = IMAGE_MANAGER->findImage(keyName);

			if (str.find("misuzu") == string::npos)	// �̽�� �ƴ� ���
			{
				characterImg.target = Vector2((float)characterImg.portrait->getWidth() / 1.5f, (float)(WINSIZEY - (100 + characterImg.portrait->getHeight() / 2.0f * 0.8f)));
				characterImg.pos = Vector2(0.0f - characterImg.portrait->getWidth() / 2, characterImg.target.y);
			}
			else
			{
				characterImg.target = Vector2((float)(WINSIZEX - characterImg.portrait->getWidth() / 1.5f), (float)(WINSIZEY - (100 + characterImg.portrait->getHeight() / 2 * 0.8f)));
				characterImg.pos = Vector2((float)(WINSIZEX + characterImg.portrait->getWidth() / 2), characterImg.target.y);
			}							
								
			string characterMsg(str.substr(atPos + 1, str.length()));
			int enterCh = characterMsg.find("/");
			// "/"�� ã���� >> ��ȭ�� �ʹ� ��� ���̾�α׿� �־��
			if (enterCh != string::npos)
			{
				// ���� ���ڷ� ����
				characterMsg.replace(enterCh, 1, "\n");
			}

			_qCharacterImg.push(characterImg);
			_qCharacterMsg.push(characterMsg);			
		}
	}
	readMsg.close();


	_isPlay = true;

	_curDialog = curDialogue::ENTER;
}

bool DialogueManager::textUpdate(float elapsedTime)
{
	_elapsedSec += elapsedTime;

	if (_elapsedSec >= _textSpeed)
	{
		_elapsedSec -= _textSpeed;
		return true;
	}
	return false;
}

bool DialogueManager::findNameImg(string src, string name)
{
	if (src.find(name) != string::npos)	// ã�� �� ������
	{
		return true;
	}
	return false;
}

void DialogueManager::keyReaction()
{
	
	if (KEY_MANAGER->isStayKeyDown(VK_SPACE))
	{
		_skip.bar->update();
		_skip.bar->setGauge(++_skip.curGauge, _skip.maxGauge);
		_skip.istayDown = true;
	}
	if (KEY_MANAGER->isOnceKeyUp(VK_SPACE))
	{
		_skip.curGauge = 0;		
		_skip.istayDown = false;
	}

	if (_skip.curGauge > _skip.maxGauge)
	{		
		while (!_qCharacterImg.empty() && !_qCharacterMsg.empty())
		{
			_qCharacterImg.pop();
			_qCharacterMsg.pop();

			_writeText.clear();
			_stringNum = 0;
		}

		_skip.curGauge = 0;
		_isPlay = false;
	}
}
