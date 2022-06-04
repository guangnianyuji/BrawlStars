#ifndef __PAUSESCENE_H__
#define __PAUSESCENE_H__

#include "cocos2d.h"
#include "BSScene\BaseScene.h"
#include "BSScene\StartScene.h"

class PauseScene :public BaseScene
{
public:
	static  PauseScene* create(cocos2d::RenderTexture* renderTexture);

	bool init() override;
};


#endif // !__PAUSESCENE_H__

