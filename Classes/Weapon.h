#ifndef __WEAPON__
#define __WEAPON__

#include "cocos2d.h"

class Hero;

class Weapon:public cocos2d::Sprite
{
public:

	static Weapon* create(const std::string& filename, Hero* Owner);

	Hero* getOwner() { return m_Owner; }

	void setPhyBody();


private:
	Hero* m_Owner;
};
#endif

