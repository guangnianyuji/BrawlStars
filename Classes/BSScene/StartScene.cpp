#include "StartScene.h"


cocos2d::Scene* StartScene::create()
{
    StartScene* pRet = new(std::nothrow) StartScene(); 
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

bool StartScene::init()
{
    if (!BaseScene::init())
    {
        return false;
    }

    Vec2 visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    this->drawBackGround(cocos2d::Sprite::create("scene_graph/background1.png"));

    //SocketManager::getInstance()->start();

    auto RoomButton = Button::create("ui/Play.png");
	RoomButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
		{
            auto roomscene = RoomScene::create();
            if (roomscene != nullptr)
            {
                Director::getInstance()->pushScene(roomscene);
            }
			
		});
	RoomButton->setPosition(Vec2(visibleSize.x/2, visibleSize.y / 6));
	addChild(RoomButton);


    return true;
}
