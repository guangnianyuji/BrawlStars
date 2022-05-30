#ifndef __PHYSICS_MANAGER__
#define __PHYSICS_MANAGER__

#include "cocos2d.h"
#include "PhysicsListener.h"
#include "Box2D/Box2D.h"

class PhysicsManager
{
private:

	PhysicsManager();
	~PhysicsManager();
public:
	static PhysicsManager* getInstance();

	/* ������������ */
	void setPhysicsWorld(cocos2d::PhysicsWorld*);

	/* �õ��������� */
	cocos2d::PhysicsWorld* getPhysicsWorld();
	
	/* ������������ */
	void updateWorld(float dt);

private:
	static PhysicsManager* m_Instance;
	cocos2d::PhysicsWorld* m_World;
	cocos2d::EventListenerPhysicsContact* m_ContactListener;
};

#endif

