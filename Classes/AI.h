#ifndef __AI_H__
#define __AI_H__

#include "Hero.h"
#include "Character.h"


class AI:public Hero
{
public:
    //根据所选角色创建AI
    static AI* create(Character);
protected:
    //初始化玩家
    virtual bool init() override;

};

#endif // !__AI_H__


