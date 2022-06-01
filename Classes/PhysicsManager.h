#ifndef __PHYSICS_MANAGER__
#define __PHYSICS_MANAGER__

#include "cocos2d.h"

class PhysicsManager
{
private:
	PhysicsManager();
	~PhysicsManager();
public:
	static PhysicsManager* getInstance();

	void startContactListen();

	void onContactBegin();

private:

	static PhysicsManager* m_Instance;

	cocos2d::EventListenerPhysicsContact* m_ContactListener = nullptr;
};

#endif

