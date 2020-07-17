#pragma once
#include <unordered_map>

enum class ObjectType : int
{
	TileObject, Monster, Player,Item ,UI,End
};

//게임오브젝트를 관리하는 클래스
class ObjectManager final : public singletonBase<ObjectManager>
{
	unordered_map<ObjectType, vector<class GameObject*>> mObjectContainer;
	typedef unordered_map<ObjectType, vector<class GameObject*>>::iterator ObjectContainerIter;
public:
	ObjectManager();
	~ObjectManager();

	void Release();
	void Update();
	void Render();

	void AddObject(ObjectType objectType,class GameObject* newObject);
	void RemoveObject(ObjectType objectType,class GameObject* deleteObject);

	class GameObject* FindObject(ObjectType objectType,string objectName);
	vector<class GameObject*> FindObjects(ObjectType objectType,string objectName);
	vector<class GameObject*>& GetObjectList(ObjectType objectType);
};

