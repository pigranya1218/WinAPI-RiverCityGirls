#include "stdafx.h"
#include "CameraManager.h"

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
}

void CameraManager::merge(int s, int e) // merge sort
{
	if (s == e) return;
	int mid = (s + e) / 2;
	merge(s, mid);
	merge(mid + 1, e);

	sort(s, e);
}

void CameraManager::sort(int s, int e)
{
	int sIndex = s;
	int eIndex = e;
	int mid = (s + e) / 2;
	vector<tagZImage> tempVector;

	while (sIndex <= mid && mid + 1 <= eIndex)
	{
		if (_renderList[sIndex].pos.z <= _renderList[eIndex].pos.z)
		{
			tempVector.push_back(_renderList[sIndex]);
			sIndex++;
		}
		else
		{
			tempVector.push_back(_renderList[eIndex]);
			eIndex--;
		}
	}
	while (sIndex <= mid)
	{
		tempVector.push_back(_renderList[sIndex]);
		sIndex++;
	}
	while (mid + 1 <= eIndex)
	{
		tempVector.push_back(_renderList[eIndex]);
		eIndex--;
	}

	for (int i = 0; i <= (e - s); i++) // 정렬
	{
		_renderList[s + i] = tempVector[i];
	}
}

void CameraManager::render(tagZImage imageInfo)
{
	// 그림자 그리기
	shadow(imageInfo.pos, imageInfo.size);

	// 타입에 맞게 이미지 그리기
	switch (imageInfo.renderType)
	{
	case IMAGE_RENDER_TYPE::RENDER:
	{
		render(imageInfo.img, getRelativeV2(convertV3ToV2(imageInfo.pos)));
	}
	break;
	case IMAGE_RENDER_TYPE::RENDER_WITH_SOURCE_POS:
	{
		render(imageInfo.img, getRelativeV2(convertV3ToV2(imageInfo.pos)), imageInfo.sourPos, imageInfo.sourSize);
	}
	break;
	case IMAGE_RENDER_TYPE::FRAME_RENDER: 
	{
		frameRender(imageInfo.img, getRelativeV2(convertV3ToV2(imageInfo.pos)), imageInfo.frameX, imageInfo.frameY);
	}
	break;
	case IMAGE_RENDER_TYPE::ANIMATION_RENDER:
	{
		aniRender(imageInfo.img, getRelativeV2(convertV3ToV2(imageInfo.pos)), imageInfo.ani);
	}
	break;
	}
}

Vector2 CameraManager::convertV3ToV2(Vector3 v3)
{
	return Vector2(v3.x, (v3.y + v3.z));
}

HRESULT CameraManager::init()
{
	return S_OK;
}

void CameraManager::release()
{
}

void CameraManager::setConfig(float L, float T, float width, float height, float minL, float minT, float maxL, float maxT)
{
	_L = L;
	_T = T;
	_width = width;
	_height = height;
	_originMinL = _minL = minL;
	_originMinT = _minT = minT;
	_originMaxL = _maxL = maxL;
	_originMaxT = _maxT = maxT;

	_x = _L + (_width / 2);
	_y = _T + (_height / 2);
	_originMinX = _minX = _minL + (_width / 2);
	_originMinY = _minY = _minT + (_height / 2);
	_originMaxX = _maxX = _maxL + (_width / 2);
	_originMaxY = _maxY = _maxT + (_height / 2);
}

void CameraManager::setConfigCenter(float x, float y, float width, float height, float minX, float minY, float maxX, float maxY)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_originMinX = _minX = minX;
	_originMinY = _minY = minY;
	_originMaxX = _maxX = maxX;
	_originMaxY = _maxY = maxY;

	_L = _x - (width / 2);
	_T = _y - (height / 2);
	_originMinL = _minL = _minX - (width / 2);
	_originMinT = _minT = _minY - (height / 2);
	_originMaxL = _maxL = _maxX - (width / 2);
	_originMaxT = _maxT = _minY - (height / 2);
}

float CameraManager::getL()
{
	return _L;
}

float CameraManager::getT()
{
	return _T;
}

Vector2 CameraManager::getLT()
{
	return Vector2(_L, _T);
}

float CameraManager::getX()
{
	return _x;
}

float CameraManager::getY()
{
	return _y;
}

Vector2 CameraManager::getXY()
{
	return Vector2(_x, _y);
}

void CameraManager::setL(float newL)
{
	newL = min(_maxL, newL);
	newL = max(_minL, newL);
	_L = floor(newL);
	_x = _L + (_width / 2);
}

void CameraManager::setT(float newT)
{
	newT = min(_maxT, newT);
	newT = max(_minT, newT);
	_T = floor(newT);
	_y = _T + (_height / 2);
}

void CameraManager::setLT(Vector2 newLT)
{
	setL(newLT.x);
	setT(newLT.y);
}

void CameraManager::setX(float newX)
{
	newX = min(_maxX, newX);
	newX = max(_minX, newX);
	_x = floor(newX);
	_L = _x - (_width / 2);
}

void CameraManager::setY(float newY)
{
	newY = min(_maxY, newY);
	newY = max(_minY, newY);
	_y = floor(newY);
	_T = _y - (_height / 2);
}

void CameraManager::setXY(Vector2 newXY)
{
	setX(newXY.x);
	setY(newXY.y);
}

void CameraManager::movePivot(float offsetX, float offsetY)
{
	setL(_L + offsetX);
	setT(_T + offsetY);
}

void CameraManager::movePivot(Vector2 offsetXY)
{
	setL(_L + offsetXY.x);
	setT(_T + offsetXY.y);
}

float CameraManager::getRelativeX(float left)
{
	float newL = left - _L;
	return newL;
}

LONG CameraManager::getRelativeX(LONG left)
{
	LONG newL = left - _L;
	return newL;
}

float CameraManager::getRelativeY(float top)
{
	float newT = top - _T;
	return  newT;
}

LONG CameraManager::getRelativeY(LONG top)
{
	LONG newT = top - _T;
	return  newT;
}

Vector2 CameraManager::getRelativeV2(Vector2 vec2)
{
	return Vector2(getRelativeX(vec2.x), getRelativeY(vec2.y));
}

FloatRect CameraManager::getRelativeFR(FloatRect rc)
{
	return FloatRect(getRelativeX(rc.left), getRelativeY(rc.top),
		getRelativeX(rc.right), getRelativeY(rc.bottom));
}

float CameraManager::getAbsoluteX(float left)
{
	float newL = _L + left;
	return newL;
}

LONG CameraManager::getAbsoluteX(LONG left)
{
	LONG newL = _L + left;
	return newL;
}

float CameraManager::getAbsoluteY(float top)
{
	float newT = _T + top;
	return newT;
}

LONG CameraManager::getAbsoluteY(LONG top)
{
	LONG newT = _T + top;
	return newT;
}

Vector2 CameraManager::getAbsoluteV2(Vector2 vec2)
{
	return Vector2(getAbsoluteX(vec2.x), getAbsoluteY(vec2.y));
}

FloatRect CameraManager::getAbsoluteFR(FloatRect rc)
{
	return FloatRect(getAbsoluteX(rc.left), getAbsoluteY(rc.top),
		getAbsoluteX(rc.right), getAbsoluteY(rc.bottom));
}

void CameraManager::rectangle(FloatRect rect, D2D1::ColorF::Enum color, float alpha, float strokeWidth)
{
	FloatRect relativeRc = getRelativeFR(rect);
	D2D_RENDERER->drawRectangle(relativeRc, color, alpha, strokeWidth);
}

void CameraManager::shadow(Vector3 pos, Vector3 size)
{
	Vector2 drawPos = convertV3ToV2(pos);
	Vector2 drawSize = convertV3ToV2(size);
	D2D_RENDERER->drawEllipse(drawPos, drawSize, D2D1::ColorF::Enum::Black, 0.2);
}

void CameraManager::render(Image * img, Vector2 center)
{
	Vector2 drawPos = getRelativeV2(center);
	img->render(center);
}

void CameraManager::render(Image * img, Vector2 center, Vector2 sourLT, Vector2 sourSize)
{
	Vector2 drawPos = getRelativeV2(center);
	img->render(center, sourLT, sourSize);
}

void CameraManager::frameRender(Image * img, Vector2 center, int frameX, int frameY)
{
	Vector2 drawPos = getRelativeV2(center);
	img->frameRender(center, frameX, frameY);
}

void CameraManager::aniRender(Image * img, Vector2 center, Animation * ani)
{
	Vector2 drawPos = getRelativeV2(center);
	img->aniRender(drawPos, ani);
}

void CameraManager::renderZ(Image * img, Vector3 center, Vector3 size)
{
	tagZImage zImage;
	zImage.renderType = IMAGE_RENDER_TYPE::RENDER;
	zImage.img = img;
	zImage.pos = center;
	zImage.size = size;

	_renderList.push_back(zImage);
}

void CameraManager::renderZ(Image * img, Vector3 center, Vector3 size, Vector2 sourLT, Vector2 sourSize)
{
	tagZImage zImage;
	zImage.renderType = IMAGE_RENDER_TYPE::RENDER_WITH_SOURCE_POS;
	zImage.img = img;
	zImage.pos = center;
	zImage.size = size;
	zImage.sourPos = sourLT;
	zImage.sourSize = sourSize;

	_renderList.push_back(zImage);
}

void CameraManager::frameRenderZ(Image * img, Vector3 center, Vector3 size, int frameX, int frameY)
{
	tagZImage zImage;
	zImage.renderType = IMAGE_RENDER_TYPE::FRAME_RENDER;
	zImage.img = img;
	zImage.pos = center;
	zImage.size = size;
	zImage.frameX = frameX;
	zImage.frameY = frameY;

	_renderList.push_back(zImage);
}

void CameraManager::aniRenderZ(Image * img, Vector3 center, Vector3 size, Animation * ani)
{
	tagZImage zImage;
	zImage.renderType = IMAGE_RENDER_TYPE::ANIMATION_RENDER;
	zImage.img = img;
	zImage.pos = center;
	zImage.size = size;
	zImage.ani = ani;

	_renderList.push_back(zImage);
}

void CameraManager::renderZList()
{
	if (_renderList.size() == 0) return;
	merge(0, _renderList.size() - 1);

	for (int i = 0; i < _renderList.size(); i++)
	{
		render(_renderList[i]);
	}

	_renderList.clear();
}
