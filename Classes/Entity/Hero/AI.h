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

    //根据所选角色创建AI
    static AI* create(Character);

    //得到AI的时间
    float getTime() const { return m_TimeCounter->getTime(); }

    //获取状态机对象
    FSM* getFSM() const { return m_FSM; }

    Hero* getTarget() const { return m_Target; }

    Box* getBox() const { return m_Box; }

    void setTarget(Hero* target) { m_Target = target; }

    void setBox(Box* box) { m_Box = box; }
  
    //得到普通攻击状态
    bool getNormalAttackState() const { return m_NormalAttackState; }

    //得到大招攻击状态
    bool getACE_CD_State() const { return m_ACE_CD_State; }

    //更新大招状态
    void updateACEState();

    //更新AI的大招状态 
    bool getACEState() const { return m_ACEState; }

    //更新AI普攻的状态
    void updateNormalAttackState();

    //记录普攻次数 
    void addCount() { m_Count++; }

    void setState(EnumStateType state);

    void move(Point endposition,float speed);

    //追踪
    void trace(float delta);

    //逃跑
    void runAway(float delta);

    //散步
    void wander(float delta);

    //攻击宝箱
    void attackBox(float delta);


private:
    //初始化玩家
    virtual bool init();

    //给AI设置物理属性
    void setPhyBody();

    //设置普通攻击状态
    void setNormalAttackState(bool state) { m_NormalAttackState = state; }

    //设置大招状态
    void setACE_CD_State(bool state) { m_ACE_CD_State = state; }

    //更新AI的大招攒积状态
    void updateACE_CD_State();

    void update(float delta);

 /*   void findPath();

    void findPathAsync();

    void asynsUpdate(float delta);*/

    //void onExit() ;

    //是否开始攻击
    bool m_NormalAttackState;

    //是否开始大招攻击
    bool m_ACE_CD_State;

    bool m_ACEState;

    //记录上一次普攻的时间
    float m_LastNormalAttackTime = 0;

    //记录大招开始时间
    float m_StartACETime;

    //记录上一次大招的时间
    float m_LastACETime = 0;

    //记录普攻次数，积攒大招
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

    /* 在子线程里进行路径计算 */
    std::thread* m_FindPathThread;
};

#endif // !__AI_H__


