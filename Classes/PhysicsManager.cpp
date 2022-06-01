#include "PhysicsManager.h"

PhysicsManager* PhysicsManager::getInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new (std::nothrow) PhysicsManager;
	}
	return m_Instance;
}

void PhysicsManager::startContactListen()
{
	if(m_ContactListener != nullptr)
	{
		m_ContactListener = cocos2d::EventListenerPhysicsContact :: create();
	}
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(m_ContactListener, 2);
}

void PhysicsManager::onContactBegin()
{
}
