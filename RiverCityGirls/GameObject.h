#pragma once

class GameObject
{
protected:
	Synthesize(string, mName, Name)
	/*
	protected: string mName;
	public: inline string GetName()const{return mName;}
	public: inline void SetName(string value){mName = value;}
	*/
	Synthesize(Vector2, mPosition, Position)
	Synthesize(Vector2, mSize,Size)
	Synthesize(FloatRect, mRect,Rect) 
	Synthesize(bool, mActive,Active)
public:
	GameObject();
	virtual ~GameObject();

	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

