#include "TimeCounter.h"

bool TimeCounter::init()
{
	return true;
}

void TimeCounter::update(float dt)
{
	m_Time += dt;
}

void TimeCounter::startCounting()
{
	m_Time = 0;

	this->scheduleUpdate();
}

void TimeCounter::resetTime()
{
	m_Time = 0;
}

float TimeCounter::getTime()
{
	return m_Time;
}
