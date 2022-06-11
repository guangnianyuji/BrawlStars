#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Hero.h"
#include "Character.h"

class Player:public Hero
{
public:

    //根据所选角色创建玩家
    static Player* create(Character);


private:
    //初始化玩家
    virtual bool init() override;
    
    void setPhyBody();

};
#endif // !__PLAYER_H__
