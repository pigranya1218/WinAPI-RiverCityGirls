#include "stdafx.h"
#include "GameNode.h"

GameNode::GameNode()
{
}


GameNode::~GameNode()
{
}

HRESULT GameNode::init()
{
	_managerInit = false;


	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_managerInit = managerInit;

	if (_managerInit)
	{
	//	SetTimer(_hWnd, 1, 10, NULL);
		KEY_MANAGER->init();
		TIME_MANAGER->init();

		SOUND_MANAGER->init();
		SCENE_MANAGER->init();

		TXTDATA->init();
	}


	return S_OK;
}

void GameNode::release()
{
	if (_managerInit)
	{
	//	KillTimer(_hWnd, 1);

		KEY_MANAGER->release();
		KEY_MANAGER->releaseSingleton();

		TXTDATA->release();
		TXTDATA->releaseSingleton();

		TIME_MANAGER->release();
		TIME_MANAGER->releaseSingleton();

		SOUND_MANAGER->release();
		SOUND_MANAGER->releaseSingleton();

		SCENE_MANAGER->release();
		SCENE_MANAGER->releaseSingleton();

	}
	
	ReleaseDC(_hWnd, _hdc);
}

void GameNode::update()
{
	
}

void GameNode::render()
{

}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//HWND - 핸들메시지
	//UINT - 메시지 발생 번호
	//WPARAM - 키보드 입력 및 마우스 클릭 메시지 전달
	//LPARAM - 마우스 좌표 전달

	PAINTSTRUCT ps;
	HDC			hdc;

	switch (iMessage)
	{
	
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>(LOWORD(lParam));
			_ptMouse.y = static_cast<float>(HIWORD(lParam));
		break;

		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_ESCAPE:
					PostQuitMessage(0);
				break;

			}
		}
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
