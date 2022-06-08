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

	/* �л�״̬ */
	void changeState(State* state);

private:

	/* ��⵽���µ�Hero������Ұ����ͬһ���� */
	void newHeroInView(cocos2d::Point position);
	
	/* ��⵽�µı��������Ұ,��ͬһ���� */
	void newBoxInView(cocos2d::Point position);

	/* ���ڱ���״̬ */
	void nearDeath(cocos2d::Ref* data);

	/* ���е����� */
	void hitTheEnemy(cocos2d::Point position);

	void injured(cocos2d::Point position);

	/* ��ŵ�ǰ״̬�� */
	State* m_State;

	/* ������AI���� */
	AI* m_AI;
};

#endif // !__FSM__
