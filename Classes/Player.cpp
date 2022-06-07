#include "Player.h"

Player* Player::create(Character character) 
{ 
	Player* pRet = new(std::nothrow) Player();
	pRet->m_Character = character;

	if (pRet && pRet->init()) {
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

bool Player::init()
{
	if (!Hero::init())
	{
		return false;
	}
	
	setPhyBody();

	return true;
}

void Player::setPhyBody()
{
	/* 使Player的身体承载物理属性 */
	auto physicsBody = PhysicsBody::createBox(m_Body->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setGravityEnable(false);
	physicsBody->setCategoryBitmask(0x0001);
	physicsBody->setCollisionBitmask(0x0001);
	physicsBody->setContactTestBitmask(0x0001);
	this->setName("Player");
	this->setPhysicsBody(physicsBody);
}
