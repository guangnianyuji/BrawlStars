#ifndef __AI_H__
#define __AI_H__

#include "Hero.h"
#include "Character.h"
#include "PathFinding.h"
#include "FSM.h"
#include "ALLState.h"


class AI:public Hero
{
public:

    //������ѡ��ɫ����AI
    static AI* create(Character);

    //�õ�AI��ʱ��
    float getTime() const { return m_TimeCounter->getTime(); }

    //��ȡ״̬������
    FSM* getFSM() const { return m_FSM; }

    //�õ���ͨ����״̬
    bool getNormalAttackState() const { return m_NormalAttackState; }

    //�õ����й���״̬
    bool getACE_CD_State() const { return m_ACE_CD_State; }

    //���´���״̬
    void updateACEState();

    //����AI�Ĵ���״̬ 
    bool getACEState() const { return m_ACEState; }

    //����AI�չ���״̬
    void updateNormalAttackState();


    //��¼�չ����� 
    void addCount() { m_Count++; }



    //׷��
    void trace(cocos2d::Point position);

    //����
    void runAway(cocos2d::Point position);

    //ɢ��
    void wander();

private:
    //��ʼ�����
    virtual bool init() override;

    //��AI������������
    void setPhyBody();

    //������ͨ����״̬
    void setNormalAttackState(bool state) { m_NormalAttackState = state; }

    //���ô���״̬
    void setACE_CD_State(bool state) { m_ACE_CD_State = state; }

    //����AI�Ĵ����ܻ�״̬
    void updateACE_CD_State();

    void update(float delta) override;

    void onExit() override;

    //�Ƿ�ʼ����
    bool m_NormalAttackState;

    //�Ƿ�ʼ���й���
    bool m_ACE_CD_State;

    bool m_ACEState;

    //��¼��һ���չ���ʱ��
    float m_LastNormalAttackTime = 0;

    //��¼���п�ʼʱ��
    float m_StartACETime;

    //��¼��һ�δ��е�ʱ��
    float m_LastACETime = 0;

    //��¼�չ����������ܴ���
    int m_Count = 0;

    TimeCounter* m_TimeCounter;

    FSM* m_FSM;

    std::vector<cocos2d::Point> Path;
};

#endif // !__AI_H__


