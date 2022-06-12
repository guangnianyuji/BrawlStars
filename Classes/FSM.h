#ifndef __FSM__
#define __FSM__

#include"cocos2d.h"
#include "Util/NotifyUtil.h"
#include "State/State.h"

class AI;

class FSM:public cocos2d::Node
{

public:
	~FSM();
	static FSM* createWithAI(AI* m_AI);
	bool initWithAI(AI* m_AI);

	/* 切换状态 */
	void changeState(State* state);

	void setMark(const std::string m_Mark);

	void addObservers();

	std::string getMark() const { return m_AIMark; }

private:

	/* 检测到有新的Hero进入视野，即同一区域 */
	void newHeroInView(Hero*);
	
	/* 检测到新的宝箱进入视野,即同一区域 */
	void newBoxInView(Box*);

	/* 处于濒死状态 */
	void nearDeath(cocos2d::Ref* data);

	/* 击中敌人了 */
	void hitTheEnemy(Hero*);

	/* 被打到了 */
	void injured(Hero*); 

	void nothingToDo(cocos2d::Ref* data);

	/* 被毒雾打到了 */
	void touchingTheSmog(cocos2d::Ref* data);

	/* 存放当前状态类 */
	State* m_State;

	/* 关联的AI对象 */
	AI* m_AI;

	std::string m_AIMark;
};

#endif // !__FSM__
