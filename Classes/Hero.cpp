#include "Hero.h"

bool Hero::init()
{
	if (!Entity::init())
	{
		return false;
	}

	m_Body = Sprite::create(m_Character.m_Name + "/" + m_Character.m_Name + "f1.png");

	if (m_Body == nullptr)
	{
		return false;
	}

	//m_Skill = Sprite::create(m_Character.m_Name + "/" + "Skill/1.png");

	//if (m_Skill == nullptr)
	//{
	//	log("hahahaha");
	//}

	m_Blood = ProgressView::create();

	if (m_Blood == nullptr)
	{
		return false;
	}

	m_Blood->setBloodVolume(m_Character.m_BloodVolume);

	this->addChild(m_Body);

	//m_Skill->setAnchorPoint(Vec2(1,-1));

	m_Blood->setAnchorPoint(Vec2(0,0));

	//m_Body->addChild(m_Skill);

	m_Body->addChild(m_Blood);

	m_Speed = m_Character.m_Speed;

	m_isMoving = false;
	m_Direction = "a";//随意初始化无意义

	/* 使Player的身体承载物理属性 */

	auto physicsBody = PhysicsBody::createBox(m_Body->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(0xFFFFFFFF);
	m_Body->setPhysicsBody(physicsBody);

	return true;
}

void Hero::beganToMove(const float& Angle)
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

	runAction(MoveBy::create(0.1f, MathUtils::getVectorialSpeed(Angle, m_Speed /150)));

	m_isMoving = true;

}

void Hero::stopMoving()
{
	if (m_isMoving)
	{
       m_Body->stopAllActions();
	   m_isMoving = false;
	   m_Direction = "a";
	}
}

void Hero::NormalAttack(const float& Angle)
{

	if (m_Character.m_Name == "F")
	{
		auto Fire1 = Sprite::create(m_Character.m_Name + "/" + "Normal_Attack/F_01.png");
		
		auto physicsBody = cocos2d::PhysicsBody::createBox(Fire1->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));

		physicsBody->setDynamic(false);

		physicsBody->setContactTestBitmask(0XFFFFFFFF);

		Fire1->setPhysicsBody(physicsBody);

		Point nowPosition = m_Body->getPosition();

		Fire1->setPosition(nowPosition);

		Fire1->setAnchorPoint(Vec2(1, 1));

		Fire1->setName("Weapon");

		this->addChild(Fire1);

		auto actionShoot = MoveTo::create(1.0f / 5, nowPosition + MathUtils::getVectorialSpeed(Angle, 200));

		auto actionBurn = AnimationUtils::createNormalAttackAnimation(m_Character.m_Name);

		auto actionRemove = RemoveSelf::create();

		Fire1->runAction(Sequence::create((Spawn::create(actionShoot, actionBurn, nullptr)), actionRemove, nullptr));

		this->BeAttacked(1.0f);
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

}

void Hero::BeAttacked(const float& Damage)
{
	float realTimeBlood = m_Blood->getRealTimeBlood() - Damage;

	m_Blood->setRealTimeBlood(realTimeBlood);

	if (realTimeBlood <= 0)
	{
		this->Death();
	}
}

void Hero::Death()
{
	//this->removeFromParentAndCleanup(true);
}

float Hero::getSpeed()
{
	return m_Speed;
}

