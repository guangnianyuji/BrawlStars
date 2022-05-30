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

	/* 设置物理世界 */
	void setPhysicsWorld(cocos2d::PhysicsWorld*);

	/* 得到物理世界 */
	cocos2d::PhysicsWorld* getPhysicsWorld();
	
	/* 更新物理世界 */
	void updateWorld(float dt);

private:
	static PhysicsManager* m_Instance;
	cocos2d::PhysicsWorld* m_World;
	cocos2d::EventListenerPhysicsContact* m_ContactListener;
};

#endif

