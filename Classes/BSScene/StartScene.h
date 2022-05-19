#ifndef __START_SCENE__
#define __START_SCENE__

#include"BaseScene.h"

class StartScene :public BaseScene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(StartScene);
};

#endif

