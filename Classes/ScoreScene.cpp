#include "ScoreScene.h"

ScoreScene* create(int rank)
{
	ScoreScene* pRet = new(std::nothrow)ScoreScene();

	auto  VisibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool ScoreScene::init()
{
	if (!BaseScene::init())
	{
		return false;
	}
	this->drawBackGround(cocos2d::Sprite::create("scene_graph/background3.png"));

}