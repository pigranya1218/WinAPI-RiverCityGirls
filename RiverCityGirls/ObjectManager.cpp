#include "stdafx.h"
#include "ObjectManager.h"

#include "GameObject.h"

ObjectManager::ObjectManager()
{
	for (int i = 0; i < (int)ObjectType::End; ++i)
	{
		mObjectContainer.insert(make_pair((ObjectType)i, vector<GameObject*>()));
	}
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Release()
{
	ObjectContainerIter iter = mObjectContainer.begin();
	for (; iter != mObjectContainer.end(); ++iter)
	{
		vector<GameObject*>& objectList = iter->second;
		for (int i = 0; i < objectList.size(); ++i)
		{
			objectList[i]->Release();
			SAFE_DELETE(objectList[i]);
		}
	}

	mObjectContainer.clear();
}

void ObjectManager::Update()
{
	ObjectContainerIter iter = mObjectContainer.begin();
	for (; iter != mObjectContainer.end(); ++iter)
	{
		vector<GameObject*>& objectList = iter->second;
		for (int i = 0; i < objectList.size(); ++i)
		{
			if (objectList[i]->GetActive())
				objectList[i]->Update();
		}
	}
}

void ObjectManager::Render()
{
	ObjectContainerIter iter = mObjectContainer.begin();
	for (; iter != mObjectContainer.end(); ++iter)
	{
		vector<GameObject*>& objectList = iter->second;
		for (int i = 0; i < objectList.size(); ++i)
		{
			if (objectList[i]->GetActive())
				objectList[i]->Render();
		}
	}
}

void ObjectManager::AddObject(ObjectType objectType, GameObject * newObject)
{
	//��,��ô���� �� �迭�����Ҷ��� �����ؾ� �ϴ� ���� �ִ�
	//���࿡ �ش� Ű���� �����Ͱ� ������ ���� �����Ѵ�
	//����� find�� �Ȱ��� �Ǿ��ִ� ���δ�
	mObjectContainer[objectType].push_back(newObject);
}

void ObjectManager::RemoveObject(ObjectType objectType, GameObject * deleteObject)
{
	vector<GameObject*>& objectList = mObjectContainer[objectType];
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

GameObject * ObjectManager::FindObject(ObjectType objectType, string objectName)
{
	vector<GameObject*>& objectList = mObjectContainer[objectType];
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
vector<class GameObject*> ObjectManager::FindObjects(ObjectType objectType, string objectName)
{
	//���� �̸� ���� �ֵ� ���� ����
	vector<GameObject*> resolt;
	//�̰Ŵ� �ش� Ÿ���� ������Ʈ�� ��Ƴ� �ʾȿ� �ִ� ������???
	vector<GameObject*>& objectList = mObjectContainer[objectType];
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

vector<class GameObject*>& ObjectManager::GetObjectList(ObjectType objectType)
{
	return mObjectContainer[objectType];
}
