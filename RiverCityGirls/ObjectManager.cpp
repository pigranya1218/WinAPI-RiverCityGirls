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

void ObjectManager::collision(Vector3 * pos)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->collision(pos);
	}
}

void ObjectManager::spawnObject(OBJECT_TYPE type, Vector3 pos, DIRECTION direction)
{
	switch (type)
	{
	case OBJECT_TYPE::DESK:
	{
		_objects.push_back(new DeskObject(pos, direction));
	}
	break;
	}
}
