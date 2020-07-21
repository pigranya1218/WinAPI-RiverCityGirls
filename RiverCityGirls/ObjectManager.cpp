#include "stdafx.h"
#include "ObjectManager.h"
#include "Object.h"

void ObjectManager::init()
{
	deskOb = new Object;
	deskOb->setObject(desk, IDLE01, WINSIZEX / 2, WINSIZEY / 2);
	deskOb->init();

	shcoolBoy01 = new Object;
	shcoolBoy01->setObject(schoolBoyE, IDLE01, WINSIZEX / 2 - 100, WINSIZEY / 2 - 100);
	shcoolBoy01->init();

	return;
}

void ObjectManager::release()
{
}

void ObjectManager::update()
{
	deskOb->update();
	shcoolBoy01->update();
}

void ObjectManager::render()
{
	deskOb->render();
	//shcoolBoy01->render();
}
