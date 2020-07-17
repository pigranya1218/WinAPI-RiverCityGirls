#pragma once

/****************************************************************************
## ImageRenderer ##
*****************************************************************************/
class ImageManager final 
{
public:
	static ImageManager* getInstance()
	{
		static ImageManager* istance = new ImageManager;
		return istance;
	}

private:
	typedef map<string, class Image*>::iterator ImageIter; 

private:
	map<string, class Image*> _imageList;

	IWICImagingFactory* _wicFactory;

public:
	ImageManager();
	virtual ~ImageManager();

	class Image* addImage(const string& key, const wstring& file);
	class Image* addFrameImage(const string& key,const wstring& file,const int maxFrameX,const int maxFrameY);
	class Image* findImage(const string& key);
private:
	ID2D1Bitmap* createD2DBitmapFromFile(const wstring& file);
	void deleteAll();
};

#define IMAGE_MANAGER ImageManager::getInstance()