#pragma once
#include"GameNode.h"

enum TagObjectType
{
	desk, deskChair, table, tableChair, pillar, snackMachine, box, mrRudis, schoolBoyA, schoolBoyB, schoolBoyE, schoolGirlA, schoolGirlB, schoolGirlE, workingFemaleA, workingMaleD
};

enum tagImageState
{
	IDLE01, IDLE02, REACTION
};

struct TagObject
{
	TagObjectType objectType;			//이미지 타입
	tagImageState objectImgState;		//이미지 상태

	bool isPlayerReactionObject;		//true : ReactionObject, false : Non-ReacionObject
	bool isObjectHuman;					//true : human			 false : Non-human
	Image* objectImg;					//image
	bool isObjectLeft;					//true : Left,			 false : Right
	int frameX;							//프레임 x
	float objectX, objectZ, objectY;	//좌표, 아마도 x,z를 통해 잡혀질듯
	float sizeWidth, sizeHeight;		//사이즈
	int stage;							//받아올 스테이지
};

class Object :
	public GameNode
{
private:
	TagObject _object;
	int _frameMax;				//최대 프레임 x값	
	int _count;					//시간
public:

	HRESULT init();
	void update();
	void release();
	void render();

	void setObject(TagObjectType _objectType, tagImageState _objectImgState, float _x, float _z, float _sizeWidth, float _sizeheight); //{ _object.objectType = objectType; _object.objectX = _x; _object.objectZ = _z; }
	//void getPlayerReaction() //플레이어와 충돌하면
};

