#pragma once
#include "GameObject.h"
#include "Player.h"

enum class OBJECT_STATE : int
{
	IDLE, // 기본 대기 상태01
	REACTION, // 반응중인 상태
	BROKEN // 이미 깨져서 이제 반응 안하는 상태
};

class Object :  public GameObject
{
protected:
	OBJECT_STATE _state;					// object state
	DIRECTION _direction;

	Image* _img;								//image
	float _imgScale = 3;
	Animation* _ani;

public:
	Object() {};
			//
	Object(Vector3 position, DIRECTION direction, int imageType);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3* newPoses, GameObject* gameObject);
	virtual void reaction();

	void getHit(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type); // 맞았는지 체크하기 위해 공통으로 사용되는 충돌 처리 함수
	virtual void hitEffect(GameObject* hitter, FloatRect attackRc, float damage, ATTACK_TYPE type); // 맞았을 때 호출되는 함수, 각 오브젝트별로 구현하기
};

