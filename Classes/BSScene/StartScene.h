#ifndef __START_SCENE__
#define __START_SCENE__

#include"BaseScene.h"
#include "BSScene/RoomScene.h"

class StartScene :public BaseScene
{
public:
	static cocos2d::Scene* create();

	virtual bool init() override;

	void addTitle();
};

#endif

