#pragma once

class GameObject
{
protected:
	Synthesize(string, _name, Name)
	/*
	protected: string mName;
	public: inline string GetName()const{return mName;}
	public: inline void SetName(string value){mName = value;}
	*/
	Synthesize(Vector3, _position, Position) // x, y, z
	Synthesize(Vector2, _size,Size)
	Synthesize(FloatRect, _rect,Rect)
	Synthesize(bool, _active,Active)
public:
	GameObject();
	virtual ~GameObject();

	virtual void init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

