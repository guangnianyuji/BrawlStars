#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Hero.h"
#include "Character.h"

class Player:public Hero
{
public:

    //������ѡ��ɫ�������
    static Player* create(Character);


private:
    //��ʼ�����
    virtual bool init() override;
    
    void setPhyBody();

};
#endif // !__PLAYER_H__