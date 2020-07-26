#pragma once
#include "singletonBase.h"

#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmodex64_vc.lib")

using namespace FMOD;

#define SOUNDBUFFER 100
#define EXTRACHANNELBUFFER 5

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER


class SoundManager : public SingletonBase<SoundManager>
{
private:
	typedef map<string, Sound**>			arrSounds;
	typedef map<string, Sound**>::iterator	arrSoundsIter;

	typedef map<string, Channel**>			 arrChannels;
	typedef map<string, Channel**>::iterator arrChannelIter;

private:
	System*			_system;
	Sound**			_sound;
	Channel**		_channel;

	arrSounds		_mTotalSounds;

public:
	SoundManager();
	~SoundManager();

	HRESULT init();
	void release();
	void update();

	void addSound(string keyName, string soundName, bool bgm, bool loop);

	void play(string keyName, float volume = 1.0f);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	//���� �̺�Ʈ ó���� (ȣ���� ���� hoxy...)
	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);
};

