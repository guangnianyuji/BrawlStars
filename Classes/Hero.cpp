#include "Hero.h"

bool Hero::init()
{
	m_Body = Sprite::create(m_Character.m_Name + "/" + m_Character.m_Name + "f1.png");

	m_Skill = Sprite::create(m_Character.m_Name + "/" + "Skill/1.png");

	RealTimeBlood = m_Character.m_BloodVolume;

	if (!Entity::init())
	{
		return false;
	}

	addChild(m_Body);

	m_Body->addChild(m_Skill);

	m_Skill->setAnchorPoint(Vec2(1,-0.5));

	m_isMoving = false;
	m_Direction = "a";//随意初始化无意义

	return true;
}

void Hero::setAnimation(const float& Angle)
{
	m_Skill->runAction(AnimationUtils::createSkillAnimation(m_Character.m_Name));

	std::string tempDirection;
	if (Angle > -3 * Pi / 4 && Angle < -Pi / 4)
	{
		tempDirection = "f";
	}
	else if (Angle < 3 * Pi / 4 && Angle > Pi / 4)
	{
		tempDirection = "b";
	}
	else if (Angle > 3 * Pi / 4 || Angle < -3 * Pi / 4)
	{
		tempDirection = "l";
	}
	else if (Angle > - Pi / 4 && Angle < 3*Pi / 4)
	{
		tempDirection = "r";
	}
	if (tempDirection != m_Direction)
	{
		m_Direction = tempDirection;
		m_Body->stopAllActions();
		m_Body->runAction(AnimationUtils::createAnimation(m_Character.m_Name, m_Direction));
	}
	runAction(MoveBy::create(0.1f, MathUtils::getVectorialSpeed(Angle, m_Character.m_Speed / 200)));
	m_isMoving = true;
}

void Hero::stopAnimation()
{
	if (m_isMoving)
	{
       m_Body->stopAllActions();
	   m_isMoving = false;
	}
}

void Hero::NormalAttack(const float& Angle)
{
	if (m_Character.m_Name == "F")
	{
		auto Fire = Sprite::create(m_Character.m_Name + "/" + "Skill/1.png");
		
		auto physicsBody = cocos2d::PhysicsBody::createBox(Fire->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
		physicsBody->setDynamic(false);
		physicsBody->setContactTestBitmask(0XFFFFFFFF);
		Fire->setPhysicsBody(physicsBody);

		Point nowPosition = m_Body->getPosition();
		Fire->setPosition(nowPosition);
		Fire->setAnchorPoint(Vec2(1, 1));
		Fire->setRotation(Angle);
		Fire->setName("Weapon");
		this->addChild(Fire);

		auto actionShoot = MoveTo::create(1.0f / 5, nowPosition + MathUtils::getVectorialSpeed(Angle, 200));

		auto actionBurn = AnimationUtils::createNormalAttackAnimation(m_Character.m_Name);

		auto actionRemove = RemoveSelf::create();

		Fire->runAction(Sequence::create((Spawn::create(actionShoot, actionBurn, nullptr)), actionRemove, nullptr));
	}

	else if (m_Character.m_Name == "Y")
	{

	}
}


void Hero::stopNormalAttack()
{
	m_Skill->runAction(AnimationUtils::createSkillAnimation(m_Character.m_Name));
}

void Hero::AttackSomething()
{
	log("hahaha");
}

void Hero::BeAttacked(const int& Damage)
{
	this->RealTimeBlood -= Damage;

	if (RealTimeBlood <= 0)
	{
		this->Death();
	}
}

void Hero::Death()
{
	this->removeFromParentAndCleanup(true);
}



