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
	//맵,언올더드맵 을 배열접근할때는 조심해야 하는 점이 있다
	//만약에 해당 키값의 데이터가 없으면 새로 생성한다
	//사실은 find랑 똑같이 되어있다 내부는
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
	//여기까지 왔으면 못찾은거 
	return nullptr;
}

//같은 이름을 가진 오브젝트 전부 찾아서 벡터로 반환
vector<class GameObject*> ObjectManager::findObjects(ObjectType objectType, string objectName)
{
	//같은 이름 가진 애들 담을 벡터
	vector<GameObject*> resolt;
	//이거는 해당 타입의 오브젝트를 모아논 맵안에 있는 벡터지???
	vector<GameObject*>& objectList = _objectContainer[objectType];
	for (int i = 0; i < objectList.size(); ++i)
	{
		//같은 이름이라면
		if (objectList[i]->GetName() == objectName)
		{
			//resolt에 담아라
			resolt.push_back(objectList[i]);
		}
	}
	//여기까징 왔다면 같은 이름을 가진 애들을 다 찾았다는 뜻이니 반환
	return resolt;
}

vector<class GameObject*>& ObjectManager::getObjectList(ObjectType objectType)
{
	return _objectContainer[objectType];
}
