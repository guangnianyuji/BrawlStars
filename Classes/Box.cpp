#include "Box.h"


Box* Box::create()
{
	Box* pRet = new(std::nothrow)Box();

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

bool Box::init()
{
	if (!Entity::init())
	{
		return false;
	}

	m_Body = Sprite::create("woodbox.png");

	auto physicsBody = PhysicsBody::createBox(m_Body->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setGravityEnable(false);
	physicsBody->setContactTestBitmask(0x1F);
	this->setName("Box");
	this->setPhysicsBody(physicsBody);

	m_Blood = ProgressView::create();

	if (m_Blood == nullptr)
	{
		return false;
	}

	m_Blood->setBloodVolume(650);

	this->addChild(m_Body);
	//m_Blood->setAnchorPoint(Vec2(0, 0));

	m_Body->addChild(m_Blood);


	m_offerBlood = 200;
	m_offerDamage = 20;

}

void Box::beAttacked(const float& Damage)
{
	if (m_isDead) return;

	float realTimeBlood = m_Blood->getRealTimeBlood() - Damage;

	m_Blood->setRealTimeBlood(realTimeBlood);

	if (realTimeBlood <= 0)
	{
		m_isDead = true;
		this->Death();
	}
}

void Box::Death()
{
	m_isDead = true;
	m_Blood->setBloodVolume(650);
}