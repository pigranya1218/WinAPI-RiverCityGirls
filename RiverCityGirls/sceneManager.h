#pragma once
#include "SingletonBase.h"


class GameNode;

class SceneManager : public SingletonBase<SceneManager>
{
public:
	typedef map<string, GameNode*>			 mapSceneList;
	typedef map<string, GameNode*>::iterator mapSceneIter;

private:
	static GameNode* _currentScene;
	mapSceneList _mSceneList;

public:
	SceneManager();
	~SceneManager();

	HRESULT init();
	void release();
	void update();
	void render();

	GameNode* addScene(string sceneName, GameNode* scene);

	HRESULT changeScene(string sceneName);

};

