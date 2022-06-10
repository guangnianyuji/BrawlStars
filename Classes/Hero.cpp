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

	m_Blood = ProgressView::create();

	if (m_Blood == nullptr)
	{
		return false;
	}

	m_Blood->setBloodVolume(m_Character.m_BloodVolume);

	this->addChild(m_Body);
	//m_Blood->setAnchorPoint(Vec2(0, 0));

	m_Body->addChild(m_Blood);

	m_Speed = m_Character.m_Speed;

	m_isMoving = false;
	m_Direction = "a";//随意初始化无意义

	m_NormalAttackDamage = m_Character.m_NormalAttackDamage;
	m_AceDamage = m_Character.m_AceDamage;

	scheduleUpdate();

	return true;
}

void Hero::beganToMove(const float& Angle,const float Speed,Point EndPosition)
{

	if (this == nullptr)
		return;
	if (this->getPosition() == EndPosition)
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
	runAction(MoveTo::create(0.5f, this->getPosition()+MathUtils::getVectorialSpeed(Angle, Speed/10.0f)));

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

void Hero::normalAttack(const float Angle)
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
		Fire1->setDamage(m_Character.m_NormalAttackDamage);
		Map->addChild(Fire1,5);
		auto actionShoot1 = MoveTo::create(1.0f / 5, nowPosition + MathUtils::getVectorialSpeed(Angle - Pi/6, m_Character.m_Range));
		auto actionBurn1 = AnimationUtils::createNormalAttackAnimation(m_Character.m_Name, 1);
		auto actionRemove1 = RemoveSelf::create();
		Fire1->runAction(Sequence::create((Spawn::create(actionShoot1, actionBurn1, nullptr)), actionRemove1, nullptr));

		Fire2->setPhyBody();
		Fire2->setPosition(nowPosition);
		Fire2->setAnchorPoint(Vec2(0.5, 0.5));
		Fire2->setName("Weapon");
		Fire2->setDamage(m_Character.m_NormalAttackDamage);
		Map->addChild(Fire2,5);
		auto actionShoot2 = MoveTo::create(1.0f / 5, nowPosition + MathUtils::getVectorialSpeed(Angle, m_Character.m_Range));
		auto actionBurn2 = AnimationUtils::createNormalAttackAnimation(m_Character.m_Name,1);
		auto actionRemove2 = RemoveSelf::create();
		Fire2->runAction(Sequence::create((Spawn::create(actionShoot2, actionBurn2, nullptr)), actionRemove2, nullptr));

		Fire3->setPhyBody();
		Fire3->setPosition(nowPosition);
		Fire3->setAnchorPoint(Vec2(0.5, 0.5));
		Fire3->setName("Weapon");
		Fire2->setDamage(m_Character.m_NormalAttackDamage);
		Map->addChild(Fire3,5);
		auto actionShoot3 = MoveTo::create(1.0f / 5, nowPosition + MathUtils::getVectorialSpeed(Angle + Pi/6, m_Character.m_Range));
		auto actionBurn3 = AnimationUtils::createNormalAttackAnimation(m_Character.m_Name, 1);
		auto actionRemove3 = RemoveSelf::create();
		Fire3->runAction(Sequence::create((Spawn::create(actionShoot3, actionBurn3, nullptr)), actionRemove3, nullptr));
	}

	else if (m_Character.m_Name == "Y")
	{

		auto Water = Weapon::create(m_Character.m_Name + "/" + "Normal_Attack/Y_01.png",this);

		Water->setPhyBody();

		Water->setPosition(nowPosition + MathUtils::getVectorialSpeed(Angle, m_Character.m_Range));

		Water->setAnchorPoint(Vec2(0.5, 0.5));

		Water->setName("Weapon");

		Water->setKind("continue");

		Water->setDamage(m_Character.m_NormalAttackDamage);

		Map->addChild(Water,5);

		auto actionBurn = AnimationUtils::createNormalAttackAnimation(m_Character.m_Name,2);

		auto actionRemove = RemoveSelf::create();

		Water->runAction(Sequence::create(actionBurn, actionRemove, nullptr));

	}

	else if (m_Character.m_Name == "J")
	{
		auto Bat=Weapon::create(m_Character.m_Name + "/" + "Normal_Attack/J_01.png", this);

		Bat->setPhyBody();

		Bat->setAnchorPoint(Vec2(0.5, 0.5));

		Bat->setPosition(nowPosition);

		Bat->setName("Weapon");

		Bat->setDamage(m_Character.m_NormalAttackDamage);

		Map->addChild(Bat, 5);

		ccBezierConfig bezier;

		bezier.controlPoint_1 = Point(nowPosition.x + 100, nowPosition.y);

		bezier.controlPoint_2 = Point(nowPosition.x + 200, nowPosition.y + 250);

		bezier.endPosition = nowPosition + MathUtils::getVectorialSpeed(Angle, m_Character.m_Range);

		auto actionFly = AnimationUtils::createNormalAttackAnimation(m_Character.m_Name, 2);

		auto actionRemove = RemoveSelf::create();

		BezierTo* bezierTo = BezierTo::create(1.0f, bezier);

		Bat->runAction(Sequence::create((Spawn::create(actionFly, bezierTo, nullptr)), actionRemove, nullptr));


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

		Light1->setName("Weapon");
		Light2->setName("Weapon");
		Light3->setName("Weapon");
		Light4->setName("Weapon");

		Light1->setDamage(m_Character.m_NormalAttackDamage);
		Light2->setDamage(m_Character.m_NormalAttackDamage);
		Light3->setDamage(m_Character.m_NormalAttackDamage);
		Light4->setDamage(m_Character.m_NormalAttackDamage);

		float x = MathUtils::getVectorialSpeed(Angle, m_Character.m_Range).x;
		float y = MathUtils::getVectorialSpeed(Angle, m_Character.m_Range).y;

		if (fabs(x) < 100.0f)
		{

			Light1->setPosition(nowPosition.x + x - 75.0f,
				nowPosition.y + y);

			Light2->setPosition(nowPosition.x + x - 25.0f,
				nowPosition.y + y);

			Light3->setPosition(nowPosition.x + x + 25.0f,
				nowPosition.y + y);

			Light4->setPosition(nowPosition.x + x + 75.0f,
				nowPosition.y + y);
		}
		else if (fabs(y) < 100.0f)
		{

			Light1->setPosition(nowPosition.x + x,
				nowPosition.y + y - 75.0f);

			Light2->setPosition(nowPosition.x + x,
				nowPosition.y + y - 25.0f);

			Light3->setPosition(nowPosition.x + x,
				nowPosition.y + y + 25.0f);

			Light4->setPosition(nowPosition.x + x,
				nowPosition.y + y + 75.0f);
		}
		else
		{
			Light1->setPosition(nowPosition.x + x/4,
				nowPosition.y + y);

			Light2->setPosition(nowPosition.x + x/2,
				nowPosition.y + y/4*3 );

			Light3->setPosition(nowPosition.x + x/4*3,
				nowPosition.y + y/2);

			Light4->setPosition(nowPosition.x + x,
				nowPosition.y + y/4 );
		}

		Light1->setName("Weapon");
		Light2->setName("Weapon");
		Light3->setName("Weapon");
		Light4->setName("Weapon");

		Light1->setKind("continue");
		Light2->setKind("continue");
		Light3->setKind("continue");
		Light4->setKind("continue");


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

	}

}


void Hero::stopNormalAttack()
{
}

void Hero::ACE(const float Angle)
{

	Point nowPosition = this->getPosition();
	Node* Map = this->getParent();

	if (m_Character.m_Name == "F")
	{

		auto Fire1 = Weapon::create(m_Character.m_Name + "/" + "Ace/FAce (1).png", this);
		auto Fire2 = Weapon::create(m_Character.m_Name + "/" + "Ace/FAce (1).png", this);
		auto Fire3 = Weapon::create(m_Character.m_Name + "/" + "Ace/FAce (1).png", this);


		Fire1->setPhyBody();
		Fire1->setPosition(nowPosition);
		Fire1->setAnchorPoint(Vec2(0.5, 0.5));
		Fire1->setName("Weapon");
		Fire1->setDamage(m_Character.m_AceDamage);
		Map->addChild(Fire1, 5);
		auto actionShoot1 = MoveTo::create(1.5f, nowPosition + MathUtils::getVectorialSpeed(Angle - Pi / 6, m_Character.m_Range*2));
		auto actionBurn1 = AnimationUtils::createACEAnimation(m_Character.m_Name, 3);
		auto actionRemove1 = RemoveSelf::create();
		Fire1->runAction(Sequence::create((Spawn::create(actionShoot1, actionBurn1, nullptr)), actionRemove1, nullptr));

		Fire2->setPhyBody();
		Fire2->setPosition(nowPosition);
		Fire2->setAnchorPoint(Vec2(0.5, 0.5));
		Fire2->setName("Weapon");
		Fire2->setDamage(m_Character.m_AceDamage);
		Map->addChild(Fire2, 5);
		auto actionShoot2 = MoveTo::create(1.5f, nowPosition + MathUtils::getVectorialSpeed(Angle, m_Character.m_Range*2));
		auto actionBurn2 = AnimationUtils::createACEAnimation(m_Character.m_Name, 3);
		auto actionRemove2 = RemoveSelf::create();
		Fire2->runAction(Sequence::create((Spawn::create(actionShoot2, actionBurn2, nullptr)), actionRemove2, nullptr));

		Fire3->setPhyBody();
		Fire3->setPosition(nowPosition);
		Fire3->setAnchorPoint(Vec2(0.5, 0.5));
		Fire3->setName("Weapon");
		Fire3->setDamage(m_Character.m_AceDamage);
		Map->addChild(Fire3, 5);
		auto actionShoot3 = MoveTo::create(1.5f , nowPosition + MathUtils::getVectorialSpeed(Angle + Pi / 6, m_Character.m_Range*2));
		auto actionBurn3 = AnimationUtils::createACEAnimation(m_Character.m_Name, 3);
		auto actionRemove3 = RemoveSelf::create();
		Fire3->runAction(Sequence::create((Spawn::create(actionShoot3, actionBurn3, nullptr)), actionRemove3, nullptr));
	}

	else if (m_Character.m_Name == "Y")
	{
		m_damageImmunity = true;
		Sprite* Protect = Sprite::create("ui/Protect.png");
		Protect->setAnchorPoint(Vec2(0.5, 0.5));
		Protect->setScale(0.8);
		this->addChild(Protect, 5);
		Protect->setName("Protect");
		

	}

	else if (m_Character.m_Name == "J")
	{
		Sprite* Smog = Sprite::create(m_Character.m_Name + "/" + "Ace/JAce (1).png");
		Smog->setAnchorPoint(Vec2(0.5, 0.5));
		this->addChild(Smog);
		Animate* actionBurn = AnimationUtils::createACEAnimation(m_Character.m_Name, 10);
		auto actionRemove = RemoveSelf::create();
		Smog->runAction(Sequence::create(actionBurn, actionRemove, nullptr));


		float realTimeBlood = m_Blood->getRealTimeBlood() * 1.50;
		m_Blood->setRealTimeBlood(realTimeBlood);

	}

	else if (m_Character.m_Name == "L")
	{
		m_Speed = 5.0;
	}
}

void Hero::stopACE()
{
	if (m_Character.m_Name == "F")
	{
	}

	else if (m_Character.m_Name == "Y")
	{
		m_damageImmunity = false;
		Node* Protect = this->getChildByName("Protect");
		if(Protect!=nullptr)
			Protect->removeFromParentAndCleanup(true);
	}

	else if (m_Character.m_Name == "J")
	{
		
	}

	else if (m_Character.m_Name == "L")
	{
		m_Speed = m_Character.m_Speed;
	}
}


void Hero::attackSomething()
{
	if (m_Character.m_Name == "J")
	{
		float realTimeBlood = m_Blood->getRealTimeBlood() + m_Character.m_NormalAttackDamage * 0.5;

		m_Blood->setRealTimeBlood(realTimeBlood);
	}
}

void Hero::beAttacked(const float& Damage)
{
	if (isDead()||damageImmunity()) return;

	float realTimeBlood = m_Blood->getRealTimeBlood() - Damage;

	m_Blood->setRealTimeBlood(realTimeBlood);

	if (realTimeBlood <= 0)
	{
		this->Death();
	}
}

void Hero::Death()
{
	m_isDead = true;
	if (this->getName() == "Player")
	{
		Label* m_Label = Label::create("GAME OVER!", "fonts\Maker Felt.ttf", 40);

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Point origin = Director::getInstance()->getVisibleOrigin();
	}
	if (this != nullptr)
	{
		this->retain();
		this->removeFromParent();
	}
}

