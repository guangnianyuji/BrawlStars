#ifndef __TIMER_COUNTER__
#define __TIMER_COUNTER__

#include "cocos2d.h"

class TimeCounter:public cocos2d::Node
{
public:
	virtual bool init() override;

	/* float dt������¼����update��������һ�α����õ����α�������������ʱ�� */
	virtual void update(float dt);

	/* ��ʼ��ʱ */
	void startCounting();

	/* ��ʱ����� */
	void resetTime();

	/* ��ȡ��ǰʱ�� */
	float getTime();

	CREATE_FUNC(TimeCounter);

private:

	float m_Time;
	
};

#endif __TIME_COUNTER__

