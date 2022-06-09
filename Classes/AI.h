#ifndef __AI_H__
#define __AI_H__

#include "Hero.h"
#include "FSM.h"
#include "StateWander.h"
#include "PathFinding.h"

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

    void setTarget(Hero* target) { m_Target = target; }

    void setBoxPosition(Point position) { m_BoxPosition = position; }

    void setState(EnumStateType state) { m_State = state; }

    //׷��
    void trace(cocos2d::Point position);

    //����
    void runAway(cocos2d::Point position);

    //ɢ��
    void wander();

private:
    //��ʼ�����
    virtual bool init();

    //��AI������������
    void setPhyBody();

    //������ͨ����״̬
    void setNormalAttackState(bool state) { m_NormalAttackState = state; }

    //���ô���״̬
    void setACE_CD_State(bool state) { m_ACE_CD_State = state; }

    //����AI�Ĵ����ܻ�״̬
    void updateACE_CD_State();

    void update(float delta);

    void findPath();

    void findPathAsync();

    void asynsUpdate(float delta);

    //void onExit() ;

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

    EnumStateType m_State;
    FSM* m_FSM;
    Hero* m_Target;
    Point m_BoxPosition;

    std::vector<cocos2d::Point> Path;

    Point startPosition;
    Point endPosition;

    /* �����߳������·������ */
    std::thread* m_FindPathThread;
};

#endif // !__AI_H__


