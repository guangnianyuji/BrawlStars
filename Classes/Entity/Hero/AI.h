#ifndef __AI_H__
#define __AI_H__

#include "Entity/Hero/Hero.h"
#include "Entity/Box.h"
#include "FSM.h"
#include "State/StateWander.h"
#include "Util/PathFinding.h"

class AI:public Hero
{
public:

    //������ѡ��ɫ����AI
    static AI* create(Character);

    //�õ�AI��ʱ��
    float getTime() const { return m_TimeCounter->getTime(); }

    //��ȡ״̬������
    FSM* getFSM() const { return m_FSM; }

    Hero* getTarget() const { return m_Target; }

    Box* getBox() const { return m_Box; }

    void setTarget(Hero* target) { m_Target = target; }

    void setBox(Box* box) { m_Box = box; }
  
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

    void setState(EnumStateType state);

    void move(Point endposition,float speed);

    //׷��
    void trace(float delta);

    //����
    void runAway(float delta);

    //ɢ��
    void wander(float delta);

    //��������
    void attackBox(float delta);


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

 /*   void findPath();

    void findPathAsync();

    void asynsUpdate(float delta);*/

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

    int stepForRunAway = 0;

    int stepForWander = 0;

    int stepForAttackBox = 0;

    int stepForTrace = 0;

    EnumStateType m_State;
    FSM* m_FSM;
    Hero* m_Target;
    Point m_TargetPosition=Vec2(0,0);
    Point m_BoxPosition = Vec2(0, 0);
    Box* m_Box;

    std::vector<cocos2d::Point> Path;

    /* �����߳������·������ */
    std::thread* m_FindPathThread;
};

#endif // !__AI_H__

