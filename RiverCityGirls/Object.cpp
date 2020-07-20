#include "stdafx.h"
#include "Object.h"

HRESULT Object::init()
{
	switch (_object.objectType)
	{
		case desk:
		{
			switch (_object.objectImgState)
			{
				case IDLE01:
				{
					_object.objectImg = IMAGE_MANAGER->addImage("desk01", L"object/03_Detention_OBJ_Desks_02.png");
				}
				break;

				case IDLE02:
				{
					_object.objectImg = IMAGE_MANAGER->addImage("desk02", L"object/03_Detention_OBJ_Desks_01.png");
				}
				break;

			}
			_object.isPlayerReactionObject = false;
			_object.isObjectHuman = false;
		}
		break;

		case schoolBoyE:
		{
			switch (_object.objectImgState)
			{
				case IDLE01:
				{
					_object.objectImg = IMAGE_MANAGER->addFrameImage("schoolBoyE01", L"object/objectHuman_update/schoolBoyE_idleA.png", 4, 2);
					_frameMax = 4;
				}
				break;

				case IDLE02:
				{
					_object.objectImg = IMAGE_MANAGER->addFrameImage("schoolBoyE02", L"object/objectHuman_update/schoolBoyE_idleB.png", 4, 2);
					_frameMax = 4;
				}
				break;

				case REACTION:
				{

				}
				break;
			}
			_object.isPlayerReactionObject = true;
			_object.isObjectHuman = true;
		}
		break;
	}
	

	_frameMax = 0;
	return S_OK;
}

void Object::update()
{
	_count++;
	
	if (_object.isObjectHuman)
	{
		if (_count == 5)
		{
			_object.frameX++;
			if (_object.frameX >= _frameMax)
			{
				_object.frameX = 0;
			}
			_count = 0;
		}
	}
}

void Object::release()
{
}

void Object::render()
{
	if (_object.isObjectHuman)
	{
		CAMERA_MANAGER->frameRenderZ(_object.objectImg, Vector3(_object.objectX, 0.0, _object.objectZ), _object.frameX, _object.isObjectLeft);
		//_object.objectImg->frameRender(Vector2(_object.objectX, _object.objectZ), _object.frameX, _object.isObjectLeft);
	}
	if (!_object.isObjectHuman)
	{
		_object.objectImg->render(Vector2(_object.objectX, _object.objectZ));
	}
}

void Object::setObject(TagObjectType objectType, tagImageState _objectImgState, float _x, float _z)
{
	_object.objectType = objectType; 
	_object.objectX = _x; 
	_object.objectZ = _z;
	if (_objectImgState == REACTION)
	{
		_object.objectImgState = IDLE01;
	}
	else if (_objectImgState != REACTION)
	{
		_object.objectImgState = _objectImgState;
	}
}
