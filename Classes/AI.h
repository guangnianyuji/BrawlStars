#ifndef __AI_H__
#define __AI_H__

#include "Hero.h"
#include "Character.h"


class AI:public Hero
{
public:
    //������ѡ��ɫ����AI
    static AI* create(Character);
protected:
    //��ʼ�����
    virtual bool init() override;

};

#endif // !__AI_H__


