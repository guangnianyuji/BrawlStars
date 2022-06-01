#include "FightControllerLayer.h"
#include "MathUtils.h"

FightControllerLayer* FightControllerLayer::create(Vec2 positon,const std::string characterName)
{
	FightControllerLayer* pRet = new(std::nothrow)FightControllerLayer();

	Vec2 VisibleSize = Director::getInstance()->getVisibleSize();

	pRet->m_AttackLayer = AttackLayer::create(Vec2(VisibleSize.x / 6 * 4.5, VisibleSize.y / 6),
	Vec2(VisibleSize.x/8*7,VisibleSize.y/2));

	pRet->m_AttackLayer->_characterName = characterName;

	pRet->m_MoveRockerBackgroundPosition = positon;

	pRet->m_MoveRockerPosition = positon;

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

void FightControllerLayer::initMoveRocker()
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
}

void FightControllerLayer::initEventListener()
{

	/* 触摸监听 */

	/* 默认情况下，cocos2dx会把鼠标左点当作触摸 */

	m_TouchListener = EventListenerTouchAllAtOnce::create();

	m_TouchListener->onTouchesBegan = [&](const std::vector<Touch*>& touches, Event* event)
	{
		
	};
	m_TouchListener->onTouchesMoved = [&](const std::vector<Touch*>& touches, Event* event)
	{
		/* 遍历所有触摸事件 */
		for (auto& touch : touches)
		{
			auto TouchPoint = touch->getLocation();
			/* 如果触摸点在屏幕的左半部分 */
			if (TouchPoint.x < 780)
			{
				m_isCanMove = true;
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
			}
			/* 如果触摸点在屏幕的右半部分 */
			else
			{

				Vec2 centre1 = m_AttackLayer->normalAttackRockerBGPosition;

				Vec2 centre2 = m_AttackLayer->aceRockerBGPosition;

				/* 触摸点在普攻摇杆范围内 */
				if (MathUtils::isTouchEffective(TouchPoint, centre1, m_AttackLayer->RockerBackgroundRadius))
				{
					//m_AttackLayer->_isAttackTime = false;

					m_AttackLayer->normalAttackRockerPosition = TouchPoint;

					m_AttackLayer->normalAttackRocker->setPosition(TouchPoint);

				
				}

				/* 触摸点在绝招摇杆范围内 */
				else if (MathUtils::isTouchEffective(TouchPoint, centre2, m_AttackLayer->RockerBackgroundRadius))
				{
					//m_AttackLayer->_isAceTime = false;

					m_AttackLayer->aceRockerPosition = TouchPoint;

					m_AttackLayer->aceRocker->setPosition(TouchPoint);
					
				}
			}
		}
	};
	m_TouchListener->onTouchesEnded = [&](const std::vector<Touch*>& touches, Event* event)
	{
		if (!m_isCanMove)
		{
			
		}
		else
		{
			m_MoveRockerPosition = m_MoveRockerBackgroundPosition;
			m_MoveRockerSprite->stopAllActions();
			m_MoveRockerSprite->runAction(MoveTo::create(0.08f, m_MoveRockerBackgroundPosition));
			m_isCanMove = false;
		}

		if (/*m_AttackLayer->isAttackTime() || */m_AttackLayer->normalAttackRockerBGPosition == m_AttackLayer->normalAttackRockerPosition)
		{
			
		}
		else
		{
			m_AttackLayer->normalAttackRocker->stopAllActions();
			m_AttackLayer->normalAttackRocker->runAction(MoveTo::create(0.08f, m_AttackLayer->normalAttackRockerBGPosition));

			m_AttackLayer->normalAttackRockerAngle = MathUtils::getRad(m_AttackLayer->normalAttackRockerBGPosition,
				m_AttackLayer->normalAttackRockerPosition);

			m_AttackLayer->normalAttackRockerPosition = m_AttackLayer->normalAttackRockerBGPosition;
			m_AttackLayer->_isAttackTime = true;
		}

		if (/*m_AttackLayer->isAceTime() || */m_AttackLayer->aceRockerBGPosition == m_AttackLayer->aceRockerPosition)
		{

		}
		else
		{
			m_AttackLayer->aceRocker->stopAllActions();
			m_AttackLayer->aceRocker->runAction(MoveTo::create(0.08f, m_AttackLayer->aceRockerBGPosition));

			m_AttackLayer->aceRockerAngle = MathUtils::getRad(m_AttackLayer->aceRockerBGPosition,
				m_AttackLayer->aceRockerPosition);

			m_AttackLayer->aceRockerPosition = m_AttackLayer->aceRockerBGPosition;
			m_AttackLayer->_isAceTime = true;
		}
	};



	/* 键盘监听 */

	m_KeyboardListener = EventListenerKeyboard::create();

	m_KeyboardListener->onKeyPressed = ([&](EventKeyboard::KeyCode keycode, Event* event)->void
		{

			switch (keycode)
			{
			case EventKeyboard::KeyCode::KEY_A:m_MoveRockerPosition.x
				-= m_MoveRockerBackgroundRadius; m_isCanMove = true;
				break;
			case EventKeyboard::KeyCode::KEY_D:m_MoveRockerPosition.x
				+= m_MoveRockerBackgroundRadius; m_isCanMove = true;
				break;
			case EventKeyboard::KeyCode::KEY_W:m_MoveRockerPosition.y
				+= m_MoveRockerBackgroundRadius; m_isCanMove = true;
				break;
			case EventKeyboard::KeyCode::KEY_S:m_MoveRockerPosition.y
				-= m_MoveRockerBackgroundRadius; m_isCanMove = true;
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
		});

	scheduleUpdate();
}

bool FightControllerLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	
	initMoveRocker();
	initEventListener();

	this->addChild(m_AttackLayer);

	return true;
}


void FightControllerLayer::startMoveRocker(bool isStop)
{
	m_MoveRockerSprite->setVisible(true);

	m_MoveRockerBackgroundSprite->setVisible(true);

	m_AttackLayer->normalAttackRocker->setVisible(true);

	m_AttackLayer->aceRocker->setVisible(true);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(m_TouchListener, 2);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(m_KeyboardListener, 2);
}

void FightControllerLayer::stopMoveRocker()
{
	m_MoveRockerSprite->setVisible(false);

	m_MoveRockerBackgroundSprite->setVisible(false);

	Director::getInstance()->getEventDispatcher()->removeEventListener(m_TouchListener);

	Director::getInstance()->getEventDispatcher()->removeEventListener(m_KeyboardListener);
}

float FightControllerLayer::getMoveRockerAngle()
{
	return m_MoveRockerAngle;
}

bool  FightControllerLayer::getisCanMove()
{
	return m_isCanMove;
}

void  FightControllerLayer::update(float delta)
{
	updateRad();
	m_AttackLayer->update(delta);
}

void FightControllerLayer::updateRad( )
{
	if (m_MoveRockerBackgroundPosition == m_MoveRockerPosition)
	{
		m_isCanMove=false;
		return;
	}
	m_MoveRockerAngle = MathUtils::getRad(m_MoveRockerBackgroundPosition, m_MoveRockerPosition);
	m_isCanMove = true;
}