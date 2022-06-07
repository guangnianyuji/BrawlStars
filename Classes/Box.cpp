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

void Box::setPhyBody()
{
	auto physicsBody = PhysicsBody::createBox(m_Body->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setGravityEnable(false);
	physicsBody->setContactTestBitmask(0x1F);
	this->setName("Box");
	this->setPhysicsBody(physicsBody);
}

bool Box::init()
{
	if (!Entity::init())
	{
		return false;
	}

	m_Body = Sprite::create("woodbox.png");

	m_Blood = ProgressView::create();

	if (m_Blood == nullptr)
	{
		return false;
	}

	setPhyBody();

	m_Blood->setBloodVolume(650);

	this->addChild(m_Body);

	m_Body->addChild(m_Blood);


	m_offerBlood = 200;
	m_offerDamage = 20;

	return true;

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