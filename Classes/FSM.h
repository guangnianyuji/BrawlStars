#ifndef __FSM__
#define __FSM__

#include"cocos2d.h"
#include "NotifyUtil.h"
#include "State.h"

class AI;

class FSM:public cocos2d::Node
{

public:
	~FSM();
	static FSM* createWithAI(AI* m_AI);
	bool initWithAI(AI* m_AI);

	/* 切换状态 */
	void changeState(State* state);

private:

	/* 检测到有新的Hero进入视野，即同一区域 */
	void newHeroInView(cocos2d::Point position);
	
	/* 检测到新的宝箱进入视野,即同一区域 */
	void newBoxInView(cocos2d::Point position);

	/* 处于濒死状态 */
	void nearDeath(cocos2d::Ref* data);

	/* 击中敌人了 */
	void hitTheEnemy(cocos2d::Point position);

	void injured(cocos2d::Point position);

	/* 存放当前状态类 */
	State* m_State;

	/* 关联的AI对象 */
	AI* m_AI;
};

#endif // !__FSM__
