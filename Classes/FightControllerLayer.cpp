#include "FightControllerLayer.h"
#include "BSMath.h"

FightControllerLayer* FightControllerLayer::create(Vec2 positon)
{
	FightControllerLayer* pRet = new(std::nothrow)FightControllerLayer();
	pRet->RockerBackgroundPosition = positon;
	pRet->RockerPosition = positon;
	pRet->isCanMove = false;
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
bool FightControllerLayer::init()
{
	RockerBackgroundSprite = Sprite::create("rockerBG.png");
	RockerBackgroundSprite->setVisible(true);
	RockerBackgroundSprite->setAnchorPoint(Vec2(0.5, 0.5));
	RockerBackgroundSprite->setPosition(RockerBackgroundPosition);
	RockerBackgroundSprite->setScale(2);
	addChild(RockerBackgroundSprite,1);

	RockerSprite = Sprite::create("rocker.png");
	RockerSprite->setVisible(false);
	RockerSprite->setAnchorPoint(Vec2(0.5, 0.5));
	RockerSprite->setPosition(RockerBackgroundPosition);
	RockerSprite->setOpacity(180);
	RockerSprite->setScale(2);
	addChild(RockerSprite,1);

	RockerBackgroundRadius = RockerBackgroundSprite->getContentSize().width * 0.5;

	//触摸移动事件
	TouchListener = EventListenerTouchOneByOne::create();

	TouchListener->onTouchBegan = ([&](Touch* touch, Event* event)->bool
		{
			Point TouchPoint = touch->getLocation();
			if (TouchPoint.x<780)
		    {
				isCanMove = true;
		    }	
		return true;
		});
	TouchListener->onTouchMoved = ([&](Touch* touch, Event* event)->void
		{
			if (!isCanMove)
			{
				return;
			}
			Point TouchPoint = touch->getLocation();
			float Angle = BSMath::getRad(RockerBackgroundPosition, TouchPoint);
			if (RockerBackgroundPosition.distance(TouchPoint) >= RockerBackgroundRadius)
			{
			    RockerSprite->setPosition(RockerBackgroundPosition +
				BSMath::PolarToRectangular(RockerBackgroundRadius, Angle));
			}
			else
			{
		        RockerSprite->setPosition(TouchPoint);		
			}
    	});
	TouchListener->onTouchEnded = ([&](Touch* touch, Event* event)->void
		{
			if (!isCanMove)
			{
				return;
			}
			RockerSprite->stopAllActions();
			RockerSprite->runAction(MoveTo::create(0.08f, RockerBackgroundPosition));
			isCanMove = false;
		});
	//键盘移动事件
	KeyboardListener = EventListenerKeyboard::create();

	KeyboardListener->onKeyPressed = ([&](EventKeyboard::KeyCode keycode, Event* event)
		{
			switch (keycode)
			{
			case EventKeyboard::KeyCode::KEY_A:RockerPosition.x 
				 -=RockerBackgroundRadius; break;
			case EventKeyboard::KeyCode::KEY_D:RockerPosition.x 
				+= RockerBackgroundRadius; break;
			case EventKeyboard::KeyCode::KEY_W:RockerPosition.y 
				+= RockerBackgroundRadius; break;
			case EventKeyboard::KeyCode::KEY_S:RockerPosition.y 
				-= RockerBackgroundRadius; break;
			}
			RockerSprite->setPosition(RockerPosition);
		});
		
	KeyboardListener->onKeyReleased = ([&](EventKeyboard::KeyCode keycode, Event* event)
		{
			switch (keycode)
			{
			case EventKeyboard::KeyCode::KEY_A:RockerPosition.x
				+= RockerBackgroundRadius; break;
			case EventKeyboard::KeyCode::KEY_D:RockerPosition.x
				-= RockerBackgroundRadius; break;
			case EventKeyboard::KeyCode::KEY_W:RockerPosition.y
				-= RockerBackgroundRadius; break;
			case EventKeyboard::KeyCode::KEY_S:RockerPosition.y
				+= RockerBackgroundRadius; break;
			}
			RockerSprite->setPosition(RockerPosition);
		});
	return true;
}


void FightControllerLayer::startRocker(bool isStop)
{
	RockerSprite->setVisible(true);
	RockerBackgroundSprite->setVisible(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(TouchListener, 2);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(KeyboardListener, 2);
}

void FightControllerLayer::stopRocker()
{
	RockerSprite->setVisible(false);
	RockerBackgroundSprite->setVisible(false);
	Director::getInstance()->getEventDispatcher()->removeEventListener(TouchListener);
	Director::getInstance()->getEventDispatcher()->removeEventListener(KeyboardListener);
}

void FightControllerLayer::update(float dt)
{

}
