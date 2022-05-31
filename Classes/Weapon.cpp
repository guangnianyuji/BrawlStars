#include "Weapon.h"

Weapon* Weapon::create(const std::string& filename,Hero* Owner)
{
    Weapon* weapon = new (std::nothrow) Weapon();
    if (weapon && weapon->initWithFile(filename))
    {
        weapon->m_Owner = Owner;
        weapon->autorelease();
        return weapon;
    }
    CC_SAFE_DELETE(weapon);
    return nullptr;
}

void Weapon::setPhyBody()
{
    auto physicsBody = cocos2d::PhysicsBody::createBox(this->getContentSize() / 4, cocos2d::PhysicsMaterial(0.0f, 0.0f, 0.0f));
    physicsBody->setDynamic(false);
    physicsBody->setContactTestBitmask(0XFFFFFFFF);
    this->setPhysicsBody(physicsBody);
}



