#pragma once
#include "image.h"

class GameNode
{
private:
	bool _managerInit;		//�Ŵ����� �ʱ�ȭ�Ҳ���

public:
	GameNode();
	virtual ~GameNode();

	//HRESULT�� ����ũ�μ���Ʈ ���� ����� ��ȯ�� �ε�
	//S_OK, E_FAIL, SUCCDED ������ ���â�� 
	//����� �ʱ�ȭ�� �ߵƴ��� �ƴ����� �����ش�
	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual HRESULT init(bool managerInit);
	virtual void release();			//�޸� ���� ����
	virtual void update();			//���� ����
	virtual void render();			//�׸��� ����

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

