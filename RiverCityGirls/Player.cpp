#include "stdafx.h"
#include "Player.h"

#include "Obstacle.h"

Player::Player()
{
	_name = "Player";
	_position = Vector2(WINSIZEX / 2, WINSIZEY / 2);
	_size = Vector2(50, 50);
	_rect = rectMakePivot(_position, _size, Pivot::Center);
	_active = true;
	_img = ImageManager::getInstance()->findImage("TestFrameObject");
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(true, true);
	_ani->setFPS(20);
	_ani->start();
}


Player::~Player()
{
}

void Player::init()
{
	
}

void Player::release()
{
}

void Player::update()
{
	if(KEYMANAGER->isStayKeyDown('A'))
	{
		//왼쪽
		move(Vector2(-1.f, 0.f), 100.f);
	}
	else if (KEYMANAGER->isStayKeyDown('D'))
	{
		//오른쪽
		move(Vector2(1.f, 0.f), 100.f);
	}

	vector<GameObject*>& monsterList = OBJECTMANAGER->getObjectList(ObjectType::Monster);
	for (int i = 0; i < monsterList.size(); ++i)
	{
		RECT temp;
		if (IntersectRect(&temp, &monsterList[i]->GetRect().getRect(), &_rect.getRect()))
		{
			//충돌했으면 뭐해라~
		}
	}

	_ani->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void Player::render()
{
	D2DRenderer::GetInstance()->drawRectangle(_rect,
		D2DRenderer::DefaultBrush::Red,1.f);

	_img->aniRender(Vector2(WINSIZEX / 2, WINSIZEY / 2), _ani);
	_img->frameRender(Vector2(100, 100), 2, 0);
}

void Player::move(Vector2 moveDirection, float speed)
{
	//예시 1
	_position.x += moveDirection.x * speed * TIMEMANAGER->getElapsedTime();
	_position.y += moveDirection.y * speed * TIMEMANAGER->getElapsedTime();
	_rect = rectMakePivot(_position, _size, Pivot::Center);

	////예시 2
	//mPosition += moveDirection * speed * TIMEMANAGER->getElapsedTime();
	//mRect = RectMakePivot(mPosition, mSize, Pivot::Center);
}

void Player::moveAngle(float angle, float speed)
{
	_position.x += cosf(angle) * speed * TIMEMANAGER->getElapsedTime();
	_position.y -= sinf(angle) * speed * TIMEMANAGER->getElapsedTime();
	_rect.update(_position, _size,Pivot::Center);
}
