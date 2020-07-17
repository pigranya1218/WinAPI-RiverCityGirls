#pragma once
#include <unordered_map>

enum class ObjectType : int
{
	TileObject, Monster, Player,Item ,UI,End
};

//게임오브젝트를 관리하는 클래스
class ObjectManager final : public SingletonBase<ObjectManager>
{
	unordered_map<ObjectType, vector<class GameObject*>> _objectContainer;
	typedef unordered_map<ObjectType, vector<class GameObject*>>::iterator objectContainerIter;
public:
	ObjectManager();
	~ObjectManager();

	void release();
	void update();
	void render();

	void addObject(ObjectType objectType,class GameObject* newObject);
	void removeObject(ObjectType objectType,class GameObject* deleteObject);

	class GameObject* findObject(ObjectType objectType,string objectName);
	vector<class GameObject*> findObjects(ObjectType objectType,string objectName);
	vector<class GameObject*>& getObjectList(ObjectType objectType);
};

