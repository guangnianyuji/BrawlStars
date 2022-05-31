#ifndef __TIMER_COUNTER__
#define __TIMER_COUNTER__

#include "cocos2d.h"

class TimeCounter:public cocos2d::Node
{
public:
	virtual bool init() override;

	/* float dt参数记录的是update函数从上一次被调用到本次被调用所经过的时间 */
	virtual void update(float dt);

	/* 开始计时 */
	void startCounting();

	/* 将时间归零 */
	void resetTime();

	/* 获取当前时间 */
	float getTime();

	CREATE_FUNC(TimeCounter);

private:

	float m_Time;
	
};

#endif __TIME_COUNTER__

