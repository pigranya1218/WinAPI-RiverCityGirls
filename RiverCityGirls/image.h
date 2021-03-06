#pragma once
#include "Animation.h"

class Image final
{
public:
	struct TagLoadedImageInfo
	{
		string key;
		wstring directory;

		TagLoadedImageInfo() {}
		TagLoadedImageInfo(const string& key,const wstring& directory)
			:key(key), directory(directory) {}
	};
	struct tagFrameRect
	{
		float x;
		float y;
		float width;
		float height;
	};
private:
	ID2D1Bitmap*		_bitmap;
	float				_alpha;			

	Vector2				_size;			
	float				_scale;			
	float				_angle;
	
	Vector2				_skewPos, _skewAngle;	// ��׷�Ʈ�� ��ǥ, ����

	TagLoadedImageInfo	_loadInfo;		

	vector<Image::tagFrameRect>	_frameInfo;
	int							_maxFrameX;
	int							_maxFrameY;
private:
	friend class ImageManager;
	Image() = delete;
	Image( ID2D1Bitmap*const bitmap,const TagLoadedImageInfo& loadinfo);
	Image( ID2D1Bitmap*const bitmap,const TagLoadedImageInfo& loadinfo,const int maxFrameX,const int maxFrameY);
	virtual ~Image();
	Image operator = (const Image& image) {}
public:
	void render(const Vector2& position);
	void render(const Vector2& position, const Vector2& sourPos, const Vector2& sourSize);	
	void frameRender(const Vector2& position, const int frameX, const int frameY);
	void aniRender(const Vector2& position, Animation* ani);
	void maskRender(const Vector2& position, const Vector2& sourPos, const Vector2& sourSize, D2D1::ColorF::Enum color, float alpha);

	void resetRenderOption();

	void setSize(const Vector2& vec) { this->_size = vec; }
	void setAlpha(const float alpha) { this->_alpha = alpha; }
	void setScale(const float scale) { this->_scale = scale; }
	void setAngle(const float angle) { this->_angle = angle; }

	float getScale() { return _scale; }
	float getAngle() { return _angle; }
	float getAlpha() { return _alpha; }
	
	void setSkew(const Vector2& pos, const Vector2& angle) { this->_skewPos = pos; this->_skewAngle = angle; }

	const int getMaxFrameX()const{ return _maxFrameX; }
	const int getMaxFrameY()const{ return _maxFrameY; }
	const string getKey() const { return this->_loadInfo.key; }
	const UINT getWidth() const{ return _bitmap->GetPixelSize().width; }
	const UINT getHeight()const{ return _bitmap->GetPixelSize().height; }
	const Vector2 getSize()const { return this->_size; }
	Vector2 getFrameSize(const int& frame = 0) const { return Vector2(_frameInfo[frame].width, _frameInfo[frame].height); }
	const TagLoadedImageInfo& getLoadInfo() const { return _loadInfo; }
};

