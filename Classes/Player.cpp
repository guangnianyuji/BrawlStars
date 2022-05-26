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

	/* ʹPlayer����������������� */
	auto physicsBody = PhysicsBody::createBox(m_Body->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(0xFFFFFFFF);
	m_Body->setPhysicsBody(physicsBody);


	
	return true;
}