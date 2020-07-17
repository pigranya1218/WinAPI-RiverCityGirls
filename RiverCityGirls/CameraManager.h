#pragma once
#include "Image.h"

class CameraManager : public SingletonBase<CameraManager>
{
public:
	enum class IMAGE_RENDER_TYPE : UINT
	{
		RENDER,
		RENDER_WITH_SOURCE_POS,
		FRAME_RENDER,
		ANIMATION_RENDER
	};

	struct tagZImage
	{
		Image* img;
		Vector3 pos;
		Vector2 sourPos; // render with sour
		Vector2 sourSize; // render with sour 
		int frameX, frameY; // frameRender
		Animation* ani; // aniRender
		IMAGE_RENDER_TYPE renderType;
	};

private:
	vector<tagZImage> _renderList;

	float _L, _T; // ī�޶� LEFT, TOP ���� ��ǥ�̸� �̸� �������� �׷���
	float _x, _y; // ī�޶� ���� ��ǥ
	float _width, _height; // ī�޶� �ʺ�, ���� ��

	// �⺻��
	float _originMinL, _originMaxL;
	float _originMinT, _originMaxT;
	float _originMinX, _originMaxX;
	float _originMinY, _originMaxY;

	// zoom���� ���� ����� ����
	float _minL, _maxL; // Left ��ǥ�� ������ ����
	float _minT, _maxT; // Top ��ǥ�� ������ ����
	float _minX, _maxX; // x ��ǥ�� ������ ����
	float _minY, _maxY; // y ��ǥ�� ������ ����

private:
	void merge(int s, int e);
	void sort(int s, int e);
	void render(tagZImage imageInfo);
	Vector2 convertV3ToV2(Vector3 v3);

public:
	CameraManager();
	~CameraManager();

	HRESULT init();
	void release();

	void setConfig(float left, float top, float width, float height, float minL, float minT, float maxL, float maxT);
	void setConfigCenter(float x, float y, float width, float height, float minX, float minY, float maxX, float maxY);
	float getL();
	float getT();
	Vector2 getLT();
	float getX();
	float getY();
	Vector2 getXY();
	void setL(float newL);
	void setT(float newT);
	void setLT(Vector2 newLT);
	void setX(float newX);
	void setY(float newY);
	void setXY(Vector2 newXY);
	void movePivot(float offsetX, float offsetY);
	void movePivot(Vector2 offsetXY);

	float getRelativeX(float left);
	LONG getRelativeX(LONG left);
	float getRelativeY(float top);
	LONG getRelativeY(LONG top);
	Vector2 getRelativeV2(Vector2 vec2);
	FloatRect getRelativeFR(FloatRect rc);

	float getAbsoluteX(float left);
	LONG getAbsoluteX(LONG left);
	float getAbsoluteY(float top);
	LONG getAbsoluteY(LONG top);
	Vector2 getAbsoluteV2(Vector2 vec2);
	FloatRect getAbsoluteFR(FloatRect rc);

	void rectangle(FloatRect rect, D2D1::ColorF::Enum color, float alpha, float strokeWidth);

	void render(Image* img, Vector2 center);
	void render(Image* img, Vector2 center, Vector2 sourLT, Vector2 sourSize);

	void frameRender(Image* img, Vector2 center, int frameX, int frameY);

	void aniRender(Image* img, Vector2 center, Animation* ani);

	/*
		Z ORDER ���� �Լ�	
	*/
	void renderZ(Image* img, Vector3 center);
	void renderZ(Image* img, Vector3 center, Vector2 sourLT, Vector2 sourSize);

	void frameRenderZ(Image* img, Vector3 center, int frameX, int frameY);

	void aniRenderZ(Image* img, Vector3 center, Animation* ani);

	// ���� �� �׸���
	void renderZList();
};
