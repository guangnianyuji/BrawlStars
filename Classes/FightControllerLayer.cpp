#include "FightControllerLayer.h"
#include "MathUtils.h"

FightControllerLayer* FightControllerLayer::create(Vec2 positon)
{
	FightControllerLayer* pRet = new(std::nothrow)FightControllerLayer();
	pRet->m_RockerBackgroundPosition = positon;
	pRet->m_RockerPosition = positon;
	pRet->m_isCanMove = false;
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
	if (!Layer::init())
	{
		return false;
	}
	m_RockerBackgroundSprite = Sprite::create("rockerBG.png");
	m_RockerBackgroundSprite->setVisible(true);
	m_RockerBackgroundSprite->setAnchorPoint(Vec2(0.5, 0.5));
	m_RockerBackgroundSprite->setPosition(m_RockerBackgroundPosition);
	m_RockerBackgroundSprite->setScale(2);
	addChild(m_RockerBackgroundSprite,1);

	m_RockerSprite = Sprite::create("rocker.png");
	m_RockerSprite->setVisible(false);
	m_RockerSprite->setAnchorPoint(Vec2(0.5, 0.5));
	m_RockerSprite->setPosition(m_RockerBackgroundPosition);
	m_RockerSprite->setOpacity(180);
	m_RockerSprite->setScale(2);
	addChild(m_RockerSprite,1);

	m_RockerBackgroundRadius = m_RockerBackgroundSprite->getContentSize().width * 0.5;

	//触摸移动事件
	m_TouchListener = EventListenerTouchOneByOne::create();

	m_TouchListener->onTouchBegan = ([&](Touch* touch, Event* event)->bool
		{
			Point TouchPoint = touch->getLocation();
			if (TouchPoint.x<780)
		    {
				m_isCanMove = true;
		    }	
		return true;
		});
	m_TouchListener->onTouchMoved = ([&](Touch* touch, Event* event)->void
		{
			if (!m_isCanMove)
			{
				return;
			}
			Point TouchPoint = touch->getLocation();
			float Angle = MathUtils::getRad(m_RockerBackgroundPosition, TouchPoint);
			if (m_RockerBackgroundPosition.distance(TouchPoint) >= m_RockerBackgroundRadius)
			{
				m_RockerSprite->setPosition(m_RockerBackgroundPosition +
					MathUtils::PolarToRectangular(m_RockerBackgroundRadius, Angle));
			}
			else
			{
				m_RockerSprite->setPosition(TouchPoint);
			}
    	});
	m_TouchListener->onTouchEnded = ([&](Touch* touch, Event* event)->void
		{
			if (!m_isCanMove)
			{
				return;
			}
			m_RockerSprite->stopAllActions();
			m_RockerSprite->runAction(MoveTo::create(0.08f, m_RockerBackgroundPosition));
			m_isCanMove = false;
		});
	//键盘移动事件
	m_KeyboardListener = EventListenerKeyboard::create();

	m_KeyboardListener->onKeyPressed = ([&](EventKeyboard::KeyCode keycode, Event* event)->void
		{
			switch (keycode)
			{
			case EventKeyboard::KeyCode::KEY_A:m_RockerPosition.x
				-= m_RockerBackgroundRadius; m_KeyStateMap[1] = true; m_isCanMove = true; break;
			case EventKeyboard::KeyCode::KEY_D:m_RockerPosition.x
				+= m_RockerBackgroundRadius; m_KeyStateMap[2] = true; m_isCanMove = true; break;
			case EventKeyboard::KeyCode::KEY_W:m_RockerPosition.y
				+= m_RockerBackgroundRadius; m_KeyStateMap[3] = true; m_isCanMove = true; break;
			case EventKeyboard::KeyCode::KEY_S:m_RockerPosition.y
				-= m_RockerBackgroundRadius; m_KeyStateMap[4] = true; m_isCanMove = true; break;
			}
			m_RockerSprite->setPosition(m_RockerPosition);
		});
		
	m_KeyboardListener->onKeyReleased = ([&](EventKeyboard::KeyCode keycode, Event* event)->void
		{
			switch (keycode)
			{
			case EventKeyboard::KeyCode::KEY_A:m_RockerPosition.x
				+= m_RockerBackgroundRadius; m_KeyStateMap[1] = false; break;
			case EventKeyboard::KeyCode::KEY_D:m_RockerPosition.x
				-= m_RockerBackgroundRadius; m_KeyStateMap[2] = false; break;
			case EventKeyboard::KeyCode::KEY_W:m_RockerPosition.y
				-= m_RockerBackgroundRadius; m_KeyStateMap[3] = false; break;
			case EventKeyboard::KeyCode::KEY_S:m_RockerPosition.y
				+= m_RockerBackgroundRadius; m_KeyStateMap[4] = false; break;
			}
			for (int i = 1; i < 5; i++)
			{
				m_isCanMove = m_KeyStateMap[i];
			}
			m_RockerSprite->setPosition(m_RockerPosition);
		});

	schedule(schedule_selector(FightControllerLayer::updateRad));

	return true;
}


void FightControllerLayer::startRocker(bool isStop)
{
	m_RockerSprite->setVisible(true);
	m_RockerBackgroundSprite->setVisible(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(m_TouchListener, 2);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(m_KeyboardListener, 2);
}

void FightControllerLayer::stopRocker()
{
	m_RockerSprite->setVisible(false);
	m_RockerBackgroundSprite->setVisible(false);
	Director::getInstance()->getEventDispatcher()->removeEventListener(m_TouchListener);
	Director::getInstance()->getEventDispatcher()->removeEventListener(m_KeyboardListener);
}

float FightControllerLayer::getRockerAngle()
{
	return m_RockerAngle;
}

bool  FightControllerLayer::getisCanMove()
{
	return m_isCanMove;
}

void FightControllerLayer::updateRad(float dt)
{
	m_RockerAngle = MathUtils::getRad(m_RockerBackgroundPosition, m_RockerPosition);
}