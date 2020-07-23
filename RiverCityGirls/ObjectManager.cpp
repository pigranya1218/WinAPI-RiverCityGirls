#include "stdafx.h"
#include "ObjectManager.h"
#include "AllObjects.h"

void ObjectManager::init()
{
}

void ObjectManager::release()
{
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->release();
		delete _objects[i];
	}
	_objects.clear();
}

void ObjectManager::update()
{
	for (int i = 0; i < _objects.size(); ++i)
	{
		_objects[i]->update();
	}
}

void ObjectManager::render()
{
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->render();
	}
}

void ObjectManager::collision(Vector3 * pos, const Vector3 size)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->collision(pos, size);
	}
}

void ObjectManager::spawnObject(OBJECT_TYPE type, Vector3 pos, DIRECTION direction, int imageType)
{
	switch (type)
	{
		case OBJECT_TYPE::DESK: 
		{ _objects.push_back(new DeskObject(pos, direction, imageType)); }
		break;

		case OBJECT_TYPE::BOX:	
		{ _objects.push_back(new BoxObject(pos, direction, imageType));  }
		break;

		case OBJECT_TYPE::DESK_CHAIR:
		{ _objects.push_back(new DeskChairObject(pos, direction, imageType));  }
		break;

		case OBJECT_TYPE::mrRudis: 
		{ _objects.push_back(new MrRudis(pos, direction, imageType)); }
		break;

		case OBJECT_TYPE::schoolBoyA: 
		{ _objects.push_back(new SchoolBoyA(pos, direction, imageType)); }
		break;

		case OBJECT_TYPE::schoolBoyB:
		{ _objects.push_back(new SchoolBoyB(pos, direction, imageType)); }
		break;

		case OBJECT_TYPE::schoolBoyE:
		{ _objects.push_back(new SchoolBoyE(pos, direction, imageType)); }
		break;

		case OBJECT_TYPE::schoolGirlA:
		{ _objects.push_back(new SchoolGirlA(pos, direction, imageType)); }
		break;

		case OBJECT_TYPE::schoolGirlB:
		{ _objects.push_back(new SchoolGirlB(pos, direction, imageType)); }
		break;

		case OBJECT_TYPE::schoolGirlE:
		{ _objects.push_back(new SchoolGirlE(pos, direction, imageType)); }
		break;

		case OBJECT_TYPE::workingFemaleA:
		{ _objects.push_back(new WorkingFemaleA(pos, direction, imageType)); }
		break;
		
		case OBJECT_TYPE::workingMaleD:
		{ _objects.push_back(new WorkingMaleD(pos, direction, imageType)); }
		break;

	}
}
