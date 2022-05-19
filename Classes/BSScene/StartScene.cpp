#include "StartScene.h"

cocos2d::Scene* StartScene::createScene()
{
    auto scene = StartScene::create();
    return scene;
}

bool StartScene::init()
{
    if (!BaseScene::init())
    {
        return false;
    }

    this->drawBackGround(cocos2d::Sprite::create("background.jpg"));

    return true;
}
