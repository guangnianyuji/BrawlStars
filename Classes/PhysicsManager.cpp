#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
{
	if (m_ContactListener == nullptr)
	{
		/* ´´½¨Åö×²¼àÌýÆ÷ */
		m_ContactListener = cocos2d::EventListenerPhysicsContact::create();
	}

}

PhysicsManager* PhysicsManager::getInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new (std::nothrow) PhysicsManager;
	}

	return m_Instance;
}

void PhysicsManager::setPhysicsWorld(cocos2d::PhysicsWorld* pWorld)
{
	m_World = pWorld;
}

cocos2d::PhysicsWorld* PhysicsManager::getPhysicsWorld()
{
	return m_World;
}
