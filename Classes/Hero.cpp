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


	/* 使Hero的身体承载物理属性 */
	auto physicsBody = PhysicsBody::createBox(m_Body->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(true);
	physicsBody->setGravityEnable(false);
	physicsBody->setContactTestBitmask(0x1F);
	this->setName("Player");
	this->setPhysicsBody(physicsBody);

	scheduleUpdate();

	return true;
}

void Hero::beganToMove(const float& Angle)
{
	//m_Skill->runAction(AnimationUtils::createSkillAnimation(m_Character.m_Name));
	if (this == nullptr)
		return;

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

void Hero::NormalAttack(const float Angle)
{

	if (isDead()) return;

	Point nowPosition = this->getPosition();
	Node* Map = this->getParent();

	if (m_Character.m_Name == "F")
	{
		auto Fire1 = Weapon::create(m_Character.m_Name + "/" + "Normal_Attack/F_01.png", this);
		auto Fire2 = Weapon::create(m_Character.m_Name + "/" + "Normal_Attack/F_01.png",this);
		auto Fire3 = Weapon::create(m_Character.m_Name + "/" + "Normal_Attack/F_01.png",this);
		
		Fire1->setPhyBody();
		Fire1->setPosition(nowPosition);
		Fire1->setAnchorPoint(Vec2(0.5, 0.5));
		Fire1->setName("Weapon");
		Map->addChild(Fire1,5);
		auto actionShoot1 = MoveTo::create(1.0f / 5, nowPosition + MathUtils::getVectorialSpeed(Angle / 3 * 4, m_Character.m_Range));
		auto actionBurn1 = AnimationUtils::createNormalAttackAnimation(m_Character.m_Name, 1);
		auto actionRemove1 = RemoveSelf::create();
		Fire1->runAction(Sequence::create((Spawn::create(actionShoot1, actionBurn1, nullptr)), actionRemove1, nullptr));

		Fire2->setPhyBody();
		Fire2->setPosition(nowPosition);
		Fire2->setAnchorPoint(Vec2(0.5, 0.5));
		Fire2->setName("Weapon");
		Map->addChild(Fire2,5);
		auto actionShoot2 = MoveTo::create(1.0f / 5, nowPosition + MathUtils::getVectorialSpeed(Angle, m_Character.m_Range));
		auto actionBurn2 = AnimationUtils::createNormalAttackAnimation(m_Character.m_Name,1);
		auto actionRemove2 = RemoveSelf::create();
		Fire2->runAction(Sequence::create((Spawn::create(actionShoot2, actionBurn2, nullptr)), actionRemove2, nullptr));

		Fire3->setPhyBody();
		Fire3->setPosition(nowPosition);
		Fire3->setAnchorPoint(Vec2(0.5, 0.5));
		Fire3->setName("Weapon");
		Map->addChild(Fire3,5);
		auto actionShoot3 = MoveTo::create(1.0f / 5, nowPosition + MathUtils::getVectorialSpeed(Angle/3*2, m_Character.m_Range));
		auto actionBurn3 = AnimationUtils::createNormalAttackAnimation(m_Character.m_Name, 1);
		auto actionRemove3 = RemoveSelf::create();
		Fire3->runAction(Sequence::create((Spawn::create(actionShoot3, actionBurn3, nullptr)), actionRemove3, nullptr));

		this->BeAttacked(1.0f);
	}

	else if (m_Character.m_Name == "Y")
	{

		auto Water = Weapon::create(m_Character.m_Name + "/" + "Normal_Attack/Y_01.png",this);

		Water->setPhyBody();

		Water->setPosition(nowPosition + MathUtils::getVectorialSpeed(Angle, m_Character.m_Range));

		Water->setAnchorPoint(Vec2(0.5, 0.5));

		Water->setName("Weapon");

		Map->addChild(Water,5);

		auto actionBurn = AnimationUtils::createNormalAttackAnimation(m_Character.m_Name,2);

		auto actionRemove = RemoveSelf::create();

		Water->runAction(Sequence::create(actionBurn, actionRemove, nullptr));

		this->BeAttacked(1.0f);
	}

	else if (m_Character.m_Name == "J")
	{
		auto Bat=Weapon::create(m_Character.m_Name + "/" + "Normal_Attack/J_01.png", this);

		Bat->setPhyBody();

		Bat->setAnchorPoint(Vec2(0.5, 0.5));

		Bat->setPosition(nowPosition);

		Bat->setName("Weapon");

		Map->addChild(Bat, 5);

		ccBezierConfig bezier;

		bezier.controlPoint_1 = Point(nowPosition.x + 100, nowPosition.y);

		bezier.controlPoint_2 = Point(nowPosition.x + 200, nowPosition.y + 250);

		bezier.endPosition = nowPosition + MathUtils::getVectorialSpeed(Angle, m_Character.m_Range);

		auto actionFly = AnimationUtils::createNormalAttackAnimation(m_Character.m_Name, 2);

		auto actionRemove = RemoveSelf::create();

		BezierTo* bezierTo = BezierTo::create(1.0f, bezier);

		Bat->runAction(Sequence::create((Spawn::create(actionFly, bezierTo, nullptr)), actionRemove, nullptr));

		this->BeAttacked(100.0f);
	}

	else if (m_Character.m_Name == "L")
	{
		auto Light1= Weapon::create(m_Character.m_Name + "/" + "Normal_Attack/L_01.png", this);
		auto Light2 = Weapon::create(m_Character.m_Name + "/" + "Normal_Attack/L_01.png", this);
		auto Light3 = Weapon::create(m_Character.m_Name + "/" + "Normal_Attack/L_01.png", this);
		auto Light4 = Weapon::create(m_Character.m_Name + "/" + "Normal_Attack/L_01.png", this);

		Light1->setPhyBody();
		Light2->setPhyBody();
		Light3->setPhyBody();
		Light4->setPhyBody();

		Light1->setAnchorPoint(Vec2(0.5, 0.5));
		Light2->setAnchorPoint(Vec2(0.5, 0.5));
		Light3->setAnchorPoint(Vec2(0.5, 0.5));
		Light4->setAnchorPoint(Vec2(0.5, 0.5));

		Light1->setPosition(nowPosition.x+ MathUtils::getVectorialSpeed(Angle, m_Character.m_Range).x,
			nowPosition.y+ MathUtils::getVectorialSpeed(Angle, m_Character.m_Range).y / 4);

		Light2->setPosition(nowPosition.x + MathUtils::getVectorialSpeed(Angle, m_Character.m_Range).x/4*3,
			nowPosition.y + MathUtils::getVectorialSpeed(Angle, m_Character.m_Range).y / 2);

		Light3->setPosition(nowPosition.x + MathUtils::getVectorialSpeed(Angle, m_Character.m_Range).x/2,
			nowPosition.y + MathUtils::getVectorialSpeed(Angle, m_Character.m_Range).y / 4*3);

		Light4->setPosition(nowPosition.x + MathUtils::getVectorialSpeed(Angle, m_Character.m_Range).x/4,
			nowPosition.y + MathUtils::getVectorialSpeed(Angle, m_Character.m_Range).y );

		Light1->setName("Weapon");
		Light2->setName("Weapon");
		Light3->setName("Weapon");
		Light4->setName("Weapon");

		Map->addChild(Light1, 5);
		Map->addChild(Light2, 5);
		Map->addChild(Light3, 5);
		Map->addChild(Light4, 5);

		auto actionBling = AnimationUtils::createNormalAttackAnimation(m_Character.m_Name, 3);

		auto actionRemove = RemoveSelf::create();

		Light1->runAction(Sequence::create(actionBling , actionRemove, nullptr));
		Light2->runAction(Sequence::create(actionBling->clone(), actionRemove->clone(), nullptr));
		Light3->runAction(Sequence::create(actionBling->clone(), actionRemove->clone(), nullptr));
		Light4->runAction(Sequence::create(actionBling->clone(), actionRemove->clone(), nullptr));

		

		this->BeAttacked(10.0f);
	}

}


void Hero::stopNormalAttack()
{
	//m_Skill->runAction(AnimationUtils::createSkillAnimation(m_Character.m_Name));
}

void Hero::Ace(const float Angle)
{

	if (m_Character.m_Name == "F")
	{

	}

	else if (m_Character.m_Name == "Y")
	{
		m_Skill = Sprite::create("Y/Ace/1.png");

		Point nowPosition = m_Body->getPosition();

		m_Skill->setAnchorPoint(Vec2(0.5, 0.5));

		m_Body->addChild(m_Skill);
	}

	else if (m_Character.m_Name == "J")
	{
		float realTimeBlood = m_Blood->getRealTimeBlood() * 1.50;

		m_Blood->setRealTimeBlood(realTimeBlood);
	}

	else if (m_Character.m_Name == "L")
	{

	}
}

void Hero::stopAce()
{
}

void Hero::AttackSomething()
{
	if (m_Character.m_Name == "J")
	{
		float realTimeBlood = m_Blood->getRealTimeBlood() + m_Character.m_NormalAttackDamage * 0.5;

		m_Blood->setRealTimeBlood(realTimeBlood);
	}
}

void Hero::BeAttacked(const float& Damage)
{
	if (isDead()||damageImmunity()) return;

	float realTimeBlood = m_Blood->getRealTimeBlood() - Damage;

	m_Blood->setRealTimeBlood(realTimeBlood);

	if (realTimeBlood <= 0)
	{
		m_isDead = true;
		this->Death();
	}
}

void Hero::Death()
{
	//this->removeFromParentAndCleanup(true);
}

