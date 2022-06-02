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

    physicsBody->setDynamic(true);
    physicsBody->setGravityEnable(false);
    physicsBody->setCategoryBitmask(0x0001);
    physicsBody->setCollisionBitmask(0x0001);
    physicsBody->setContactTestBitmask(0x0001);
    this->setPhysicsBody(physicsBody);
}


