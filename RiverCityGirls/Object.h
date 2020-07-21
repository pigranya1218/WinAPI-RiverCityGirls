#pragma once
#include "GameObject.h"


enum TagObjectType
{
	desk, deskChair, table, tableChair, pillar, snackMachine, box, mrRudis, schoolBoyA, schoolBoyB, schoolBoyE, schoolGirlA, schoolGirlB, schoolGirlE, workingFemaleA, workingMaleD
};

enum tagImageState
{
	IDLE01, IDLE02, REACTION
};

class Object :
	public GameObject
{
private:
	TagObjectType objectType;				//�̹��� Ÿ��
	tagImageState objectImgState;			//�̹��� ����

	bool isPlayerReactionObject;			//true : ReactionObject, false : Non-ReacionObject
	bool isObjectHuman;						//true : human			 false : Non-human
	Image* objectImg;						//image
	bool isObjectLeft;						//true : Left,			 false : Right
	int frameX;								//������ x
	float objectX, objectZ, objectY;		//��ǥ, �Ƹ��� x,z�� ���� ��������
	int stage;								//�޾ƿ� ��������
	float frameSizeWidth, frameSizeHeight;	//������

	int _frameMax;				//�ִ� ������ x��	
	int _count;					//�ð�
public:

	void init();
	void update();
	void release();
	void render();

	void setObject(TagObjectType _objectType, tagImageState _objectImgState, float _x, float _z); //������Ʈ ���� - Ÿ��, ����, ��ġ x, z
	//void getPlayerReaction() //�÷��̾�� �浹�ϸ�
};

