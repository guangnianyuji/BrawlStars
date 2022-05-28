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

    Vec2 visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    this->drawBackGround(cocos2d::Sprite::create("scene_graph/background.jpg"));

    //SocketManager::getInstance()->start();

    auto RoomButton = Button::create("ui/Play.png");
	RoomButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
		{
			Director::getInstance()->replaceScene(RoomScene::create());
		});
	RoomButton->setPosition(Vec2(visibleSize.x/2, visibleSize.y / 6));
	addChild(RoomButton);


    return true;
}
