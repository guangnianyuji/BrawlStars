#include "FightControllerLayer.h"
#include "BSMath.h"

FightControllerLayer* FightControllerLayer::create()
{
	FightControllerLayer* pRet = new(std::nothrow)FightControllerLayer();
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
	auto VisibleSize = Director::getInstance()->getVisibleSize();

	RockerBackgroundSprite = Sprite::create("rockerBG.png");
	RockerBackgroundSprite->setVisible(false);
	RockerBackgroundSprite->setPosition(VisibleSize / 2);
	addChild(RockerBackgroundSprite);

	RockerSprite = Sprite::create("rocker.png");
	RockerSprite->setVisible(false);
	RockerSprite->setPosition(VisibleSize / 2);
	RockerSprite->setOpacity(180);

	RockerBackgroundPosition = VisibleSize / 2;
	RockerBackgroundRadius = RockerBackgroundSprite->getContentSize().width * 0.5;

	//触摸移动事件
	TouchListener = EventListenerTouchOneByOne::create();

	TouchListener->onTouchBegan =([&](Touch* touch, Event* event)->bool
		{
			Point TouchPoint = touch->getLocation();
			if (RockerSprite->boundingBox().containsPoint(TouchPoint));
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

	KeyboardListener== EventListenerKeyboard::create();

	KeyboardListener->onKeyPressed = ([&](EventKeyboard::KeyCode keycode, Event* event)->void
		{
			KeyStateValueMap[keycode] = true;
			RockerSprite->stopAllActions();
		});
	KeyboardListener->onKeyReleased = ([&](EventKeyboard::KeyCode keycode, Event* event)->void
		{
			KeyStateValueMap[keycode] = false;
		});
	return true;
}


void FightControllerLayer::startRocker(bool isStop)
{
	RockerSprite->setVisible(true);
	RockerBackgroundSprite->setVisible(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(KeyboardListener, 2);
}

void FightControllerLayer::stopRocker()
{
	RockerSprite->setVisible(false);
	RockerBackgroundSprite->setVisible(false);
	Director::getInstance()->getEventDispatcher()->removeEventListener(KeyboardListener);
}

