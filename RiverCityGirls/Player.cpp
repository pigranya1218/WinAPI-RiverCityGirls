#include "stdafx.h"
#include "Player.h"

#include "Obstacle.h"

Player::Player()
{
	mName = "Player";
	mPosition = Vector2(WINSIZEX / 2, WINSIZEY / 2);
	mSize = Vector2(50, 50);
	mRect = RectMakePivot(mPosition, mSize, Pivot::Center);
	mActive = true;
	mImg = ImageManager::GetInstance()->FindImage("TestFrameObject");
	mAni = new Animation;
	mAni->init(mImg->GetWidth(), mImg->GetHeight(), mImg->GetMaxFrameX(), mImg->GetMaxFrameY());
	mAni->setDefPlayFrame(true, true);
	mAni->setFPS(20);
	mAni->start();
}


Player::~Player()
{
}

void Player::Init()
{
	
}

void Player::Release()
{
}

void Player::Update()
{
	if(KEYMANAGER->isStayKeyDown('A'))
	{
		//왼쪽
		Move(Vector2(-1.f, 0.f), 100.f);
	}
	else if (KEYMANAGER->isStayKeyDown('D'))
	{
		//오른쪽
		Move(Vector2(1.f, 0.f), 100.f);
	}

	vector<GameObject*>& monsterList = OBJECTMANAGER->GetObjectList(ObjectType::Monster);
	for (int i = 0; i < monsterList.size(); ++i)
	{
		RECT temp;
		if (IntersectRect(&temp, &monsterList[i]->GetRect().GetRect(), &mRect.GetRect()))
		{
			//충돌했으면 뭐해라~
		}
	}

	mAni->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void Player::Render()
{
	D2DRenderer::GetInstance()->drawRectangle(mRect,
		D2DRenderer::DefaultBrush::Red,1.f);

	mImg->AniRender(Vector2(WINSIZEX / 2, WINSIZEY / 2), mAni);
	mImg->FrameRender(Vector2(100, 100), 2, 0);
}

void Player::Move(Vector2 moveDirection, float speed)
{
	//예시 1
	mPosition.x += moveDirection.x * speed * TIMEMANAGER->getElapsedTime();
	mPosition.y += moveDirection.y * speed * TIMEMANAGER->getElapsedTime();
	mRect = RectMakePivot(mPosition, mSize, Pivot::Center);

	////예시 2
	//mPosition += moveDirection * speed * TIMEMANAGER->getElapsedTime();
	//mRect = RectMakePivot(mPosition, mSize, Pivot::Center);
}

void Player::MoveAngle(float angle, float speed)
{
	mPosition.x += cosf(angle) * speed * TIMEMANAGER->getElapsedTime();
	mPosition.y -= sinf(angle) * speed * TIMEMANAGER->getElapsedTime();
	mRect.Update(mPosition,mSize,Pivot::Center);
}
