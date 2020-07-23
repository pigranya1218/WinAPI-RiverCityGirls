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

void ObjectManager::spawnObject(OBJECT_TYPE type, OBJECT_STATE state, Vector3 pos, DIRECTION direction)
{
	if (state == OBJECT_STATE::BROKEN || state == OBJECT_STATE::REACTION)
	{
		state = OBJECT_STATE::IDLE01;
	}

	switch (type)
	{
		case OBJECT_TYPE::DESK: 
		{ _objects.push_back(new DeskObject(state, pos, direction)); }
		break;

		case OBJECT_TYPE::BOX:	
		{ _objects.push_back(new BoxObject(state, pos, direction));  }
		break;

		case OBJECT_TYPE::DESK_CHAIR:
		{ _objects.push_back(new DeskChairObject(state, pos, direction));  }
		break;

		case OBJECT_TYPE::mrRudis: 
		{ _objects.push_back(new MrRudis(state, pos, direction)); }
		break;

		case OBJECT_TYPE::schoolBoyA: 
		{ _objects.push_back(new SchoolBoyA(state, pos, direction)); }
		break;

		case OBJECT_TYPE::schoolBoyB:
		{ _objects.push_back(new SchoolBoyB(state, pos, direction)); }
		break;

		case OBJECT_TYPE::schoolBoyE:
		{ _objects.push_back(new SchoolBoyE(state, pos, direction)); }
		break;

		case OBJECT_TYPE::schoolGirlA:
		{ _objects.push_back(new SchoolGirlA(state, pos, direction)); }
		break;

		case OBJECT_TYPE::schoolGirlB:
		{ _objects.push_back(new SchoolGirlB(state, pos, direction)); }
		break;

		case OBJECT_TYPE::schoolGirlE:
		{ _objects.push_back(new SchoolGirlE(state, pos, direction)); }
		break;

		case OBJECT_TYPE::workingFemaleA:
		{ _objects.push_back(new WorkingFemaleA(state, pos, direction)); }
		break;
		
		case OBJECT_TYPE::workingMaleD:
		{ _objects.push_back(new WorkingMaleD(state, pos, direction)); }
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
