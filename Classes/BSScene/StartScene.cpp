#include "StartScene.h"
#include "Network/SocketManager.h"

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

    //SocketManager::getInstance()->start();

    return true;
}
