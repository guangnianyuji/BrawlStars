#include "AttackLayer.h"
#include <MathUtils.h>

AttackLayer* AttackLayer::create(cocos2d::Vec2 position1, cocos2d::Vec2 position2)
{
	AttackLayer* pRet = new(std::nothrow)AttackLayer();

	cocos2d::Vec2 VisibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	pRet->normalAttackRockerBGPosition = position1;

	pRet->normalAttackRockerPosition = position1;

	pRet->aceRockerBGPosition = position2;

	pRet->aceRockerPosition = position2;

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
		initNormalAttackRocker();

		initAceRocker();

		RockerBackgroundRadius = normalAttackRocker->getContentSize().width*0.8 ;

		return true;
	}
	scheduleUpdate();
}

void AttackLayer::setAceRockerDisable()
{
	aceRocker->setVisible(false);
}

void AttackLayer::setAceRockerEnable()
{
	aceRocker->setVisible(true);
}

void AttackLayer::setNormalAttackRockerEnable()
{
	normalAttackRocker->setVisible(true);
}


void AttackLayer::setNormalAttackRockerDisable()
{
	normalAttackRocker->setVisible(false);
}

void AttackLayer::initAceRocker()
{
	aceRockerBG = cocos2d::Sprite::create("ui/Ace_BG.png");

	aceRocker = cocos2d::Sprite::create("ui/Ace_bt.png");

	if (aceRockerBG == nullptr || aceRocker == nullptr)
	{

	}
	else
	{
		aceRockerBG->setVisible(true);

		aceRocker->setVisible(false);

		aceRocker->setScale(1.5);

		aceRockerBG->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));

		aceRocker->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));

		aceRockerBG->setPosition(aceRockerBGPosition);

		aceRocker->setPosition(aceRockerPosition);

		this->addChild(aceRockerBG);

		this->addChild(aceRocker);

	}
}

/*
void AttackLayer::update(float delta)
{
	updateRad();
}
*/

/*
void AttackLayer::updateRad()
{
	if (normalAttackRockerPosition == normalAttackRockerBGPosition)
	{
		_isAttackTime = true;
	}
	else
	{
		
		normalAttackRockerPosition = normalAttackRockerBGPosition;

		normalAttackRockerAngle = MathUtils::getRad(normalAttackRockerBGPosition, normalAttackRockerPosition);
	}
	
	if (aceRockerPosition == aceRockerBGPosition)
	{
		_isAceTime = true;

	}
	else
	{
		//aceRockerAngle= MathUtils::getRad(aceRockerBGPosition, aceRockerPosition);
		aceRockerPosition = aceRockerBGPosition;

		aceRockerAngle= MathUtils::getRad(aceRockerBGPosition, aceRockerPosition);
	}
}
*/

void AttackLayer::initNormalAttackRocker()
{

	normalAttackRockerBG = cocos2d::Sprite::create("ui/Normal_Attack_BG.png");

	normalAttackRocker = cocos2d::Sprite::create("ui/Normal_Attack_bt.png");

	if (normalAttackRockerBG == nullptr || normalAttackRocker == nullptr)
	{

	}
	else
	{
		normalAttackRockerBG->setVisible(true);

		normalAttackRocker->setVisible(false);

		normalAttackRocker->setScale(1.5);

		normalAttackRockerBG->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));

		normalAttackRocker->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));

		normalAttackRockerBG->setPosition(normalAttackRockerBGPosition);

		normalAttackRocker->setPosition(normalAttackRockerPosition);

		this->addChild(normalAttackRockerBG);

		this->addChild(normalAttackRocker);

	}
}



