#include "stdafx.h"
#include "ObjectManager.h"

#include "GameObject.h"

ObjectManager::ObjectManager()
{
	for (int i = 0; i < (int)ObjectType::End; ++i)
	{
		_objectContainer.insert(make_pair((ObjectType)i, vector<GameObject*>()));
	}
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::release()
{
	objectContainerIter iter = _objectContainer.begin();
	for (; iter != _objectContainer.end(); ++iter)
	{
		vector<GameObject*>& objectList = iter->second;
		for (int i = 0; i < objectList.size(); ++i)
		{
			objectList[i]->Release();
			SAFE_DELETE(objectList[i]);
		}
	}

	_objectContainer.clear();
}

void ObjectManager::update()
{
	objectContainerIter iter = _objectContainer.begin();
	for (; iter != _objectContainer.end(); ++iter)
	{
		vector<GameObject*>& objectList = iter->second;
		for (int i = 0; i < objectList.size(); ++i)
		{
			if (objectList[i]->GetActive())
				objectList[i]->Update();
		}
	}
}

void ObjectManager::render()
{
	objectContainerIter iter = _objectContainer.begin();
	for (; iter != _objectContainer.end(); ++iter)
	{
		vector<GameObject*>& objectList = iter->second;
		for (int i = 0; i < objectList.size(); ++i)
		{
			if (objectList[i]->GetActive())
				objectList[i]->Render();
		}
	}
}

void ObjectManager::addObject(ObjectType objectType, GameObject * newObject)
{
	//��,��ô���� �� �迭�����Ҷ��� �����ؾ� �ϴ� ���� �ִ�
	//���࿡ �ش� Ű���� �����Ͱ� ������ ���� �����Ѵ�
	//����� find�� �Ȱ��� �Ǿ��ִ� ���δ�
	_objectContainer[objectType].push_back(newObject);
}

void ObjectManager::removeObject(ObjectType objectType, GameObject * deleteObject)
{
	vector<GameObject*>& objectList = _objectContainer[objectType];
	for (int i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i] == deleteObject)
		{
			objectList[i]->Release();
			SAFE_DELETE(objectList[i]);
			objectList.erase(objectList.begin() + i);
			return;
		}
	}
}

GameObject * ObjectManager::findObject(ObjectType objectType, string objectName)
{
	vector<GameObject*>& objectList = _objectContainer[objectType];
	for (int i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->GetName() == objectName)
		{
			return objectList[i];
		}
	}
	//������� ������ ��ã���� 
	return nullptr;
}

//���� �̸��� ���� ������Ʈ ���� ã�Ƽ� ���ͷ� ��ȯ
vector<class GameObject*> ObjectManager::findObjects(ObjectType objectType, string objectName)
{
	//���� �̸� ���� �ֵ� ���� ����
	vector<GameObject*> resolt;
	//�̰Ŵ� �ش� Ÿ���� ������Ʈ�� ��Ƴ� �ʾȿ� �ִ� ������???
	vector<GameObject*>& objectList = _objectContainer[objectType];
	for (int i = 0; i < objectList.size(); ++i)
	{
		//���� �̸��̶��
		if (objectList[i]->GetName() == objectName)
		{
			//resolt�� ��ƶ�
			resolt.push_back(objectList[i]);
		}
	}
	//�����¡ �Դٸ� ���� �̸��� ���� �ֵ��� �� ã�Ҵٴ� ���̴� ��ȯ
	return resolt;
}

vector<class GameObject*>& ObjectManager::getObjectList(ObjectType objectType)
{
	return _objectContainer[objectType];
}
