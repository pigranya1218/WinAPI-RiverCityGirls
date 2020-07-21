#include "stdafx.h"
#include "Object.h"

void Object::init()
{
	switch (objectType)
	{
		case desk:
		{
			switch (objectImgState)
			{
				case IDLE01:
				{
					objectImg = IMAGE_MANAGER->addImage("desk01", L"resources/images/object/03_Detention_OBJ_Desks_02.png");
				}
				break;

				case IDLE02:
				{
					objectImg = IMAGE_MANAGER->addImage("desk02", L"resources/images/object/03_Detention_OBJ_Desks_01.png");
				}
				break;

			}
			isPlayerReactionObject = false;
			isObjectHuman = false;
		}
		break;

		case schoolBoyE:
		{
			switch (objectImgState)
			{
				case IDLE01:
				{
					objectImg = IMAGE_MANAGER->addFrameImage("schoolBoyE01", L"resources/images/object/objectHuman_update/schoolBoyE_idleA.png", 4, 2);
					frameX = 0;
					_frameMax = 4;
				}
				break;

				case IDLE02:
				{
					objectImg = IMAGE_MANAGER->addFrameImage("schoolBoyE02", L"resources/images/object/objectHuman_update/schoolBoyE_idleB.png", 4, 2);
					_frameMax = 4;
					frameX = 0;
				}
				break;

				case REACTION:
				{
					objectImg = IMAGE_MANAGER->addFrameImage("schoolBoyEReaction", L"resources/images/object/objectHuman_update/schoolboyE_react.png", 3, 2);
					_frameMax = 3;
					frameX = 0;
				}
				break;
			}
			isPlayerReactionObject = true;
			isObjectHuman = true;
		}
		break;
	}
	

	_frameMax = 0;
	return;
}

void Object::update()
{
	_count++;
	
	if (isObjectHuman)
	{

		switch (objectImgState)
		{
			case IDLE01:
			{
				_frameMax = 4;
			}
			break;

			case IDLE02:
			{
				_frameMax = 4;
			}
			break;

			case REACTION:
			{
				_frameMax = 3;
			}
			break;
		}

		if (_count == 10)
		{
			frameX++;
			if (frameX >= _frameMax)
			{
				frameX = 0;
			}
			_count = 0;
		}

		//_object.frameSizeWidth = _object.objectImg->getMaxFrameX();
		//_object.frameSizeHeight = _object.objectImg->getMaxFrameY();

	}
}

void Object::release()
{
}

void Object::render()
{
	if (isObjectHuman)
	{
		CAMERA_MANAGER->frameRenderZ(objectImg, Vector3(objectX, 0.0, objectZ), Vector3(50.0f, 0.0, 80.0f), frameX, isObjectLeft, true);
		//_object.objectImg->frameRender(Vector2(_object.objectX, _object.objectZ), _object.frameX, _object.isObjectLeft);
	}
	if (!isObjectHuman)
	{
		//_object.objectImg->render(Vector2(_object.objectX, _object.objectZ));
		objectImg->setScale(3);
		CAMERA_MANAGER->renderZ(objectImg, Vector3(710, -55.0, 515), Vector3(120.0f, 110.0f, 40.0f), false);
		//CAMERA_MANAGER->rectangle(FloatRect(objectX - 2, objectZ - 2, objectX + 2, objectZ + 2), D2D1::ColorF::Enum::Black, 1, 2);
	}
}

void Object::setObject(TagObjectType objectType, tagImageState _objectImgState, float _x, float _z)
{
	objectType = objectType; 
	objectX = _x; 
	objectZ = _z;
	if (_objectImgState == REACTION)
	{
		objectImgState = IDLE01;
	}
	else if (_objectImgState != REACTION)
	{
		objectImgState = _objectImgState;
	}
}
