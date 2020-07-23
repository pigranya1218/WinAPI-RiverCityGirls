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

void ObjectManager::collision(Vector3 * pos, GameObject* gameObject)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->collision(pos, gameObject);
	}
}

void ObjectManager::spawnObject(OBJECT_TYPE type, Vector3 pos, DIRECTION direction)
{
	switch (type)
	{
		case OBJECT_TYPE::DESK01: 
		{ _objects.push_back(new DeskObject(pos, direction, 1)); }
		break;

		case OBJECT_TYPE::DESK02:
		{ _objects.push_back(new DeskObject(pos, direction, 2)); }
		break;

		case OBJECT_TYPE::DESK03:
		{ _objects.push_back(new DeskObject(pos, direction, 3)); }
		break;

		case OBJECT_TYPE::BOX:	
		{ _objects.push_back(new BoxObject(pos, direction));  }
		break;

		case OBJECT_TYPE::DESK_CHAIR01:
		{ _objects.push_back(new ChairObject(pos, direction, 1));  }
		break;

		case OBJECT_TYPE::DESK_CHAIR02:
		{ _objects.push_back(new ChairObject(pos, direction, 2));  }
		break;

		case OBJECT_TYPE::TABLE_CHAIR01:
		{ _objects.push_back(new ChairObject(pos, direction, 3));  }
		break;

		case OBJECT_TYPE::TABLE_CHAIR02:
		{ _objects.push_back(new ChairObject(pos, direction, 4));  }
		break;

		case OBJECT_TYPE::SNACKMACHINE:
		{ _objects.push_back(new SnackMachineObject(pos, direction)); }
		break;

		case OBJECT_TYPE::mrRudis: 
		{ _objects.push_back(new MrRudis(pos, direction)); }
		break;

		case OBJECT_TYPE::schoolBoyA_idle01: 
		{ _objects.push_back(new SchoolBoyA(pos, direction, 1)); }
		break;

		case OBJECT_TYPE::schoolBoyA_idle02:
		{ _objects.push_back(new SchoolBoyA(pos, direction, 2)); }
		break;

		case OBJECT_TYPE::schoolBoyB_idle01:
		{ _objects.push_back(new SchoolBoyB(pos, direction, 1)); }
		break;

		case OBJECT_TYPE::schoolBoyB_idle02:
		{ _objects.push_back(new SchoolBoyB(pos, direction, 2)); }
		break;

		case OBJECT_TYPE::schoolBoyE_idle01:
		{ _objects.push_back(new SchoolBoyE(pos, direction, 1)); }
		break;

		case OBJECT_TYPE::schoolBoyE_idle02:
		{ _objects.push_back(new SchoolBoyE(pos, direction, 2)); }
		break;

		case OBJECT_TYPE::schoolGirlA_idle01:
		{ _objects.push_back(new SchoolGirlA(pos, direction, 1)); }
		break;

		case OBJECT_TYPE::schoolGirlA_idle02:
		{ _objects.push_back(new SchoolGirlA(pos, direction, 2)); }
		break;

		case OBJECT_TYPE::schoolGirlB_idle01:
		{ _objects.push_back(new SchoolGirlB(pos, direction, 1)); }
		break;

		case OBJECT_TYPE::schoolGirlB_idle02:
		{ _objects.push_back(new SchoolGirlB(pos, direction, 2)); }
		break;

		case OBJECT_TYPE::schoolGirlE_idle01:
		{ _objects.push_back(new SchoolGirlE(pos, direction, 1)); }
		break;

		case OBJECT_TYPE::schoolGirlE_idle02:
		{ _objects.push_back(new SchoolGirlE(pos, direction, 2)); }
		break;

		case OBJECT_TYPE::workingFemaleA:
		{ _objects.push_back(new WorkingFemaleA(pos, direction)); }
		break;
		
		case OBJECT_TYPE::workingMaleD:
		{ _objects.push_back(new WorkingMaleD(pos, direction)); }
		break;
	}
}

void ObjectManager::getHit(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->getHit(hitter, attackRc, damage, type);
	}
}
