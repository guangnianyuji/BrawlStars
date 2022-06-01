#include "FightControllerLayer.h"
#include "MathUtils.h"

FightControllerLayer* FightControllerLayer::create()
{
	FightControllerLayer* pRet = new(std::nothrow)FightControllerLayer();

	Vec2 VisibleSize = Director::getInstance()->getVisibleSize();

	//pRet->m_AttackLayer = AttackLayer::create(Vec2(VisibleSize.x / 6 * 4.5, VisibleSize.y / 6),
	//Vec2(VisibleSize.x/8*7,VisibleSize.y/2));

	pRet->m_MoveRockerBackgroundPosition = Vec2(VisibleSize.x/4, VisibleSize.y / 3);
    pRet->m_MoveRockerPosition = Vec2(VisibleSize.x / 4, VisibleSize.y / 3);

	pRet->m_NormalAttackRockerBackgroundPosition = Vec2(VisibleSize.x / 6 * 4.5, VisibleSize.y / 6);
	pRet->m_NormalAttackRockerPosition = Vec2(VisibleSize.x / 6 * 4.5, VisibleSize.y / 6);
	
	pRet->m_ACERockerBackgroundPosition = Vec2(VisibleSize.x / 8 * 7, VisibleSize.y / 2);
	pRet->m_ACERockerPosition = Vec2(VisibleSize.x / 8 * 7, VisibleSize.y / 2);

	pRet->m_MoveRockerIsMoving = false;
	pRet->m_NormalAttackRockerIsMoving = false;
	pRet->m_ACERockerIsMoving = false;

	pRet->m_NormalAttackState = false;
	pRet->m_ACEState = false;

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

void FightControllerLayer::initMoveandAttackRocker()
{
	m_MoveRockerBackgroundSprite = Sprite::create("rockerBG.png");
	m_MoveRockerBackgroundSprite->setVisible(true);
	m_MoveRockerBackgroundSprite->setAnchorPoint(Vec2(0.5, 0.5));
	m_MoveRockerBackgroundSprite->setPosition(m_MoveRockerBackgroundPosition);
	m_MoveRockerBackgroundSprite->setScale(2);
	addChild(m_MoveRockerBackgroundSprite, 1);

	m_MoveRockerSprite = Sprite::create("rocker.png");
	m_MoveRockerSprite->setVisible(false);
	m_MoveRockerSprite->setAnchorPoint(Vec2(0.5, 0.5));
	m_MoveRockerSprite->setPosition(m_MoveRockerBackgroundPosition);
	m_MoveRockerSprite->setOpacity(180);
	m_MoveRockerSprite->setScale(2);
	addChild(m_MoveRockerSprite, 1);
	//m_MoveRockerSprite->retain();

	m_MoveRockerBackgroundRadius = m_MoveRockerBackgroundSprite->getContentSize().width * 0.5;

	m_NormalAttackRockerBackgroundSprite = Sprite::create("ui/Normal_Attack_BG.png");
	m_NormalAttackRockerBackgroundSprite->setVisible(true);
	m_NormalAttackRockerBackgroundSprite->setAnchorPoint(Vec2(0.5, 0.5));
	m_NormalAttackRockerBackgroundSprite->setPosition(m_NormalAttackRockerBackgroundPosition);
	addChild(m_NormalAttackRockerBackgroundSprite, 1);

	m_NormalAttackRockerSprite = Sprite::create("ui/Normal_Attack_bt.png");
	m_NormalAttackRockerSprite->setVisible(false);
	m_NormalAttackRockerSprite->setAnchorPoint(Vec2(0.5, 0.5));
	m_NormalAttackRockerSprite->setPosition(m_NormalAttackRockerBackgroundPosition);
	m_NormalAttackRockerSprite->setOpacity(180);
	addChild(m_NormalAttackRockerSprite, 1);

	m_NormalAttackRockerBackgroundRadius = m_NormalAttackRockerBackgroundSprite->getContentSize().width * 0.5;

	m_ACERockerBackgroundSprite = Sprite::create("ui/Ace_BG.png");
	m_ACERockerBackgroundSprite->setVisible(true);
	m_ACERockerBackgroundSprite->setAnchorPoint(Vec2(0.5, 0.5));
	m_ACERockerBackgroundSprite->setPosition(m_ACERockerBackgroundPosition);
	addChild(m_ACERockerBackgroundSprite, 1);

	m_ACERockerSprite = Sprite::create("ui/Ace_bt.png");
	m_ACERockerSprite->setVisible(false);
	m_ACERockerSprite->setAnchorPoint(Vec2(0.5, 0.5));
	m_ACERockerSprite->setPosition(m_ACERockerBackgroundPosition);
	m_ACERockerSprite->setOpacity(180);
	addChild(m_ACERockerSprite, 1);

	m_ACERockerBackgroundRadius = m_ACERockerBackgroundSprite->getContentSize().width * 0.5;
}

void FightControllerLayer::initEventListener()
{

	Vec2 VisibleSize = Director::getInstance()->getVisibleSize();
	/* 触摸监听 */

	/* 默认情况下，cocos2dx会把鼠标左点当作触摸 */

	m_TouchListener = EventListenerTouchAllAtOnce::create();

	m_TouchListener->onTouchesBegan = [&](const std::vector<Touch*>& touches, Event* event)
	{
		for (auto& touch : touches)
		{
			auto TouchPoint = touch->getLocation();
			//int i=VisibleSize.x / 2;
			if (TouchPoint.x < 780)
			{
				m_MoveRockerIsMoving = true;
			}
			else if ((MathUtils::isTouchEffective(TouchPoint, m_NormalAttackRockerBackgroundPosition, m_NormalAttackRockerBackgroundRadius)))
			{
				m_NormalAttackRockerIsMoving=true;
			}
			else if ((MathUtils::isTouchEffective(TouchPoint, m_ACERockerBackgroundPosition, m_ACERockerBackgroundRadius)))
			{
				m_ACERockerIsMoving = true;
			}
		}
		
	};
	m_TouchListener->onTouchesMoved = [&](const std::vector<Touch*>& touches, Event* event)
	{
		/* 遍历所有触摸事件 */
		for (auto& touch : touches)
		{
			auto TouchPoint = touch->getLocation();
			if(m_MoveRockerIsMoving)
			{

				float Angle = MathUtils::getRad(m_MoveRockerBackgroundPosition, TouchPoint);
				if (m_MoveRockerBackgroundPosition.distance(TouchPoint) >= m_MoveRockerBackgroundRadius)
				{
					m_MoveRockerPosition = m_MoveRockerBackgroundPosition +
						MathUtils::PolarToRectangular(m_MoveRockerBackgroundRadius, Angle);

					m_MoveRockerSprite->setPosition(m_MoveRockerPosition);
				}
				else
				{
					m_MoveRockerPosition = TouchPoint;

					m_MoveRockerSprite->setPosition(m_MoveRockerPosition);
				}
				if (m_MoveRockerBackgroundPosition == m_MoveRockerPosition)
				{
					m_MoveRockerIsMoving = false;
				}
			}
			else if(m_NormalAttackRockerIsMoving)
			{
				float Angle = MathUtils::getRad(m_NormalAttackRockerBackgroundPosition, TouchPoint);
				if (m_NormalAttackRockerBackgroundPosition.distance(TouchPoint) >= m_NormalAttackRockerBackgroundRadius)
				{
					m_NormalAttackRockerPosition = m_NormalAttackRockerBackgroundPosition +
						MathUtils::PolarToRectangular(m_NormalAttackRockerBackgroundRadius, Angle);

					m_NormalAttackRockerSprite->setPosition(m_NormalAttackRockerPosition);
				}
				else
				{
					m_NormalAttackRockerPosition = TouchPoint;

					m_NormalAttackRockerSprite->setPosition(m_NormalAttackRockerPosition);
				}
			}
			else if (m_ACERockerIsMoving)
			{
				float Angle = MathUtils::getRad(m_ACERockerBackgroundPosition, TouchPoint);
				if (m_ACERockerBackgroundPosition.distance(TouchPoint) >= m_ACERockerBackgroundRadius)
				{
					m_ACERockerPosition = m_ACERockerBackgroundPosition +
						MathUtils::PolarToRectangular(m_ACERockerBackgroundRadius, Angle);

					m_ACERockerSprite->setPosition(m_ACERockerPosition);
				}
				else
				{
					m_ACERockerPosition = TouchPoint;

					m_ACERockerSprite->setPosition(m_ACERockerPosition);
				}
			}
		}
	};
	m_TouchListener->onTouchesEnded = [&](const std::vector<Touch*>& touches, Event* event)
	{
		if (!m_MoveRockerIsMoving)
		{
			
		}
		else
		{
			m_MoveRockerPosition = m_MoveRockerBackgroundPosition;
			m_MoveRockerSprite->stopAllActions();
			m_MoveRockerSprite->runAction(MoveTo::create(0.08f, m_MoveRockerPosition));
			m_MoveRockerIsMoving = false;
		}

		if (!m_NormalAttackRockerIsMoving)
		{
			
		}
		else
		{
			//这个判断一定放在移回之前
		   if (m_NormalAttackRockerBackgroundPosition != m_NormalAttackRockerPosition)
			{ 
				m_NormalAttackState = true;
				m_NormalAttackRockerAngle = MathUtils::getRad(m_NormalAttackRockerBackgroundPosition, m_NormalAttackRockerPosition);
			}	
		   m_NormalAttackRockerPosition = m_NormalAttackRockerBackgroundPosition;
		   m_NormalAttackRockerSprite->stopAllActions();
			m_NormalAttackRockerSprite->runAction(MoveTo::create(0.08f, m_NormalAttackRockerPosition));
			m_NormalAttackRockerIsMoving = false;
		}

		if (!m_ACERockerIsMoving)
		{

		}
		else
		{
			//这个判断一定放在移回之前
			if (m_ACERockerBackgroundPosition != m_ACERockerPosition)
			{
				m_ACEState = true;
				m_ACERockerAngle = MathUtils::getRad(m_NormalAttackRockerBackgroundPosition, m_NormalAttackRockerPosition);
			}
			m_ACERockerPosition = m_ACERockerBackgroundPosition;
			m_ACERockerSprite->stopAllActions();
			m_ACERockerSprite->runAction(MoveTo::create(0.08f, m_ACERockerPosition));
			m_ACERockerIsMoving = false;
			
		}

	};



	/* 键盘监听 */

	m_KeyboardListener = EventListenerKeyboard::create();

	m_KeyboardListener->onKeyPressed = ([&](EventKeyboard::KeyCode keycode, Event* event)->void
		{

			switch (keycode)
			{
			case EventKeyboard::KeyCode::KEY_A:m_MoveRockerPosition.x
				-= m_MoveRockerBackgroundRadius; m_MoveRockerIsMoving = true;
				break;
			case EventKeyboard::KeyCode::KEY_D:m_MoveRockerPosition.x
				+= m_MoveRockerBackgroundRadius; m_MoveRockerIsMoving = true;
				break;
			case EventKeyboard::KeyCode::KEY_W:m_MoveRockerPosition.y
				+= m_MoveRockerBackgroundRadius; m_MoveRockerIsMoving = true;
				break;
			case EventKeyboard::KeyCode::KEY_S:m_MoveRockerPosition.y
				-= m_MoveRockerBackgroundRadius; m_MoveRockerIsMoving = true;
				break;
			}
			m_MoveRockerSprite->setPosition(m_MoveRockerPosition);

		});

	m_KeyboardListener->onKeyReleased = ([&](EventKeyboard::KeyCode keycode, Event* event)->void
		{
			switch (keycode)
			{
			case EventKeyboard::KeyCode::KEY_A:m_MoveRockerPosition.x
				+= m_MoveRockerBackgroundRadius;
				break;
			case EventKeyboard::KeyCode::KEY_D:m_MoveRockerPosition.x
				-= m_MoveRockerBackgroundRadius;
				break;
			case EventKeyboard::KeyCode::KEY_W:m_MoveRockerPosition.y
				-= m_MoveRockerBackgroundRadius;
				break;
			case EventKeyboard::KeyCode::KEY_S:m_MoveRockerPosition.y
				+= m_MoveRockerBackgroundRadius;
				break;
			}
			m_MoveRockerSprite->setPosition(m_MoveRockerPosition);
			if (m_MoveRockerBackgroundPosition == m_MoveRockerPosition)
			{
				m_MoveRockerIsMoving = false;
			}
	
		});

	scheduleUpdate();
}

bool FightControllerLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	
	initMoveandAttackRocker();
	initEventListener();
	setTouchEnabled(true);

	return true;
}


void FightControllerLayer::startAllRockers(bool isStop)
{
	m_MoveRockerSprite->setVisible(true);

	m_MoveRockerBackgroundSprite->setVisible(true);

	m_NormalAttackRockerSprite->setVisible(true);

	m_NormalAttackRockerBackgroundSprite->setVisible(true);

	m_ACERockerSprite->setVisible(true);

	m_ACERockerBackgroundSprite->setVisible(true);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(m_TouchListener, 2);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(m_KeyboardListener, 2);
}

void FightControllerLayer::stopAllRockers()
{
	m_MoveRockerSprite->setVisible(false);

	m_MoveRockerBackgroundSprite->setVisible(false);

	m_NormalAttackRockerSprite->setVisible(false);

	m_NormalAttackRockerBackgroundSprite->setVisible(false);

	m_ACERockerSprite->setVisible(false);

	m_ACERockerBackgroundSprite->setVisible(false);

	Director::getInstance()->getEventDispatcher()->removeEventListener(m_TouchListener);

	Director::getInstance()->getEventDispatcher()->removeEventListener(m_KeyboardListener);
}

void  FightControllerLayer::update(float delta)
{
	updateMoveRad();
}

void FightControllerLayer::updateMoveRad( )
{
	if(m_MoveRockerIsMoving&& m_MoveRockerBackgroundPosition != m_MoveRockerPosition)
	{
        m_MoveRockerAngle = MathUtils::getRad(m_MoveRockerBackgroundPosition, m_MoveRockerPosition);
	}
	
}