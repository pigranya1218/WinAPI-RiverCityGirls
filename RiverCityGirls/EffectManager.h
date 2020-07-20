#pragma once
#include "SingletonBase.h"
#include <vector>
#include <map>

class Effect;

class EffectManager : public SingletonBase<EffectManager>
{
private:
	using vEffects = vector<Effect*>;
	using mEffects = map<string, vEffects>;

private:
	mEffects _totalEffect;

public:
	EffectManager();
	~EffectManager();

	void init();
	void release();
	void update();
	void render();

	void addEffect(string effectName, const char* imageName,
		int imageWidth, int imageHeight, int effectWidth, int effectHeight,
		int fps, int buffer);

	void play(string effectName, int x, int y);
	void play(string effectName, int x, int y, int width, int height);


};

