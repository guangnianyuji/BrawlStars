#include "AttackLayer.h"

AttackLayer* AttackLayer::create(cocos2d::Vec2 position1, cocos2d::Vec2 position2)
{
	AttackLayer* pRet = new(std::nothrow)AttackLayer();

	cocos2d::Vec2 VisibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	pRet->normalAttackButtonPosition = position1;

	pRet->aceButtonPosition = position2;

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

bool AttackLayer::init()
{

	if (!cocos2d::Layer::init())
	{
		return false;
	}
	else
	{
		initNormalAttackButton();

		initAceButton();

		return true;
	}
}

void AttackLayer::initNormalAttackButton()
{
    normalAttackButton_Normal = cocos2d::Sprite::create("ui/Attack_Normal.png");

	normalAttackButton_Pressed = cocos2d::Sprite::create("ui/Attack_Pressed.png");

    if (normalAttackButton_Normal == nullptr)
    {

    }
    else
    { 
        normalAttackButton_Normal->setVisible(false);

		normalAttackButton_Normal->setScale(1.5);

		normalAttackButton_Pressed->setVisible(false);

		normalAttackButton_Pressed->setScale(1.5);

        normalAttackButton_Normal->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));

		normalAttackButton_Pressed->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));

		normalAttackButton_Normal->setPosition(normalAttackButtonPosition);

		normalAttackButton_Pressed->setPosition(normalAttackButtonPosition);

        this->addChild(normalAttackButton_Normal);

		this->addChild(normalAttackButton_Pressed);

		TouchListener = cocos2d::EventListenerTouchOneByOne::create();

		TouchListener->onTouchBegan = ([&](cocos2d::Touch* touch, cocos2d::Event* event)->bool
			{
				cocos2d::Point TouchPoint = touch->getLocation();
				
				/* 在屏幕右侧任意地方点击将可进行普攻 */
				if (TouchPoint.x > 780)
				{

					//cocos2d::log("heiheihei");
					_isAttacking = true;
				}
				return true;
			});
		TouchListener->onTouchMoved = ([&](cocos2d::Touch* touch, cocos2d::Event* event)->void
			{
				if (!_isAttacking)
				{
					return;
				}
				
				else
				{
					normalAttackButton_Normal->setVisible(false);

					normalAttackButton_Pressed->setVisible(true);
				}
			});
		TouchListener->onTouchEnded = ([&](cocos2d::Touch* touch, cocos2d::Event* event)->void
			{
				if (!isAttacking())
				{
					return;
				}
				normalAttackButton_Normal->setVisible(true);

				normalAttackButton_Pressed->setVisible(false);

				_isAttacking = false;
			});



		KeyboardListener = cocos2d::EventListenerKeyboard::create();

		KeyboardListener->onKeyPressed = ([&](cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)->void
			{
				switch (keycode)
				{
				case cocos2d::EventKeyboard::KeyCode::KEY_J:
					_isAttacking = true;
					normalAttackButton_Normal->setVisible(false);
					normalAttackButton_Pressed->setVisible(true);
					break;
				}
			});

		KeyboardListener->onKeyReleased = ([&](cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)->void
			{
				switch (keycode)
				{
				case cocos2d::EventKeyboard::KeyCode::KEY_J:
					_isAttacking = false;
					normalAttackButton_Normal->setVisible(true);
					normalAttackButton_Pressed->setVisible(false);
					break;
				}
			});
    }

	scheduleUpdate();
}

void AttackLayer::initAceButton()
{
}

void AttackLayer::setButtonEnable()
{
	normalAttackButton_Normal->setVisible(true);

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(TouchListener, 1);

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(KeyboardListener, 1);
}


