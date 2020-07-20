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
	TagObjectType objectType;			//�̹��� Ÿ��
	tagImageState objectImgState;		//�̹��� ����

	bool isPlayerReactionObject;		//true : ReactionObject, false : Non-ReacionObject
	bool isObjectHuman;					//true : human			 false : Non-human
	Image* objectImg;					//image
	bool isObjectLeft;					//true : Left,			 false : Right
	int frameX;							//������ x
	float objectX, objectZ, objectY;	//��ǥ, �Ƹ��� x,z�� ���� ��������
	float sizeWidth, sizeHeight;		//������
	int stage;							//�޾ƿ� ��������
};

class Object :
	public GameNode
{
private:
	TagObject _object;
	int _frameMax;				//�ִ� ������ x��	
	int _count;					//�ð�
public:

	HRESULT init();
	void update();
	void release();
	void render();

	void setObject(TagObjectType _objectType, tagImageState _objectImgState, float _x, float _z, float _sizeWidth, float _sizeheight); //{ _object.objectType = objectType; _object.objectX = _x; _object.objectZ = _z; }
	//void getPlayerReaction() //�÷��̾�� �浹�ϸ�
};

