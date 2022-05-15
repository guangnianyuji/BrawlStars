#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "FightControllerLayer.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto ControllerLayer = FightControllerLayer::create(Vec2(400,270));
    ControllerLayer->startRocker(true);
    addChild(ControllerLayer,2);
}


