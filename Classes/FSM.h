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

	void setMark(const std::string m_Mark);

	void addObservers();

	std::string getMark() const { return m_AIMark; }

private:

	/* ��⵽���µ�Hero������Ұ����ͬһ���� */
	void newHeroInView(Hero*);
	
	/* ��⵽�µı��������Ұ,��ͬһ���� */
	void newBoxInView(Box*);

	/* ���ڱ���״̬ */
	void nearDeath(cocos2d::Ref* data);

	/* ���е����� */
	void hitTheEnemy(Hero*);

	/* ������ */
	void injured(Hero*); 

	void nothingToDo(cocos2d::Ref* data);

	/* ��������� */
	void touchingTheSmog(cocos2d::Ref* data);

	/* ��ŵ�ǰ״̬�� */
	State* m_State;

	/* ������AI���� */
	AI* m_AI;

	std::string m_AIMark;
};

#endif // !__FSM__
