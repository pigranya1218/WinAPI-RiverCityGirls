#pragma once
class EventManager
{
public:
	//�̱��� ����� ����߿� �ϳ�
	//����� ������� �̱������ ��������
	//1) ����� ������ �Ⱦ�����
	//2) �����Ϳ���(���������δ� BSS)
	//3) ���������� ó�� ȣ���ϸ� instance �޸𸮸� ��´�
	static EventManager* GetInstance()
	{
		static EventManager instance;
		return &instance;
	}
private:
	//�䷸�� �ϸ� �ܺο��� ������ ������~
	EventManager();
	~EventManager();
public:
	//�̺�Ʈ ���� ����
	//���⿡ ���� ������� �̺�Ʈ�� ó���� ����
	vector<class IEvent*> mEventQueue;

	void Update();
	void AddEvent(class IEvent* pEvent);
};

