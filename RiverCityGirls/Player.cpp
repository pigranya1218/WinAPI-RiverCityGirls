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
	_img = IMAGE_MANAGER->findImage("TestFrameObject");
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
	if(KEY_MANAGER->isStayKeyDown('A'))
	{
		//����
		move(Vector2(-1.f, 0.f), 100.f);
	}
	else if (KEY_MANAGER->isStayKeyDown('D'))
	{
		//������
		move(Vector2(1.f, 0.f), 100.f);
	}

	vector<GameObject*>& monsterList = OBJECT_MANAGER->getObjectList(ObjectType::Monster);
	for (int i = 0; i < monsterList.size(); ++i)
	{
		RECT temp;
		if (IntersectRect(&temp, &monsterList[i]->GetRect().getRect(), &_rect.getRect()))
		{
			//�浹������ ���ض�~
		}
	}

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());
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
	//���� 1
	_position.x += moveDirection.x * speed * TIME_MANAGER->getElapsedTime();
	_position.y += moveDirection.y * speed * TIME_MANAGER->getElapsedTime();
	_rect = rectMakePivot(_position, _size, Pivot::Center);

	////���� 2
	//mPosition += moveDirection * speed * TIMEMANAGER->getElapsedTime();
	//mRect = RectMakePivot(mPosition, mSize, Pivot::Center);
}

void Player::moveAngle(float angle, float speed)
{
	_position.x += cosf(angle) * speed * TIME_MANAGER->getElapsedTime();
	_position.y -= sinf(angle) * speed * TIME_MANAGER->getElapsedTime();
	_rect.update(_position, _size,Pivot::Center);
}
