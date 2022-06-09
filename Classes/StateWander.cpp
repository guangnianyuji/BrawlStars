#include "StateWander.h"

void StateWander::execute(AI* m_AI, EnumStateType state)
{
	switch (state)
	{
	case WantToWander:
		m_AI->setState(state);
		m_AI->getFSM()->changeState(new (std::nothrow) StateWander());
		break;
	case WantToRunAway:
		m_AI->unschedule(schedule_selector(AI::wander));
		m_AI->setState(state);
		m_AI->getFSM()->changeState(new (std::nothrow) StateRunAway());
		m_AI->schedule(schedule_selector(AI::runAway), 0.5f);
	default:
		break;
	}
}

void StateWander::execute(AI* m_AI, EnumStateType state, cocos2d::Point position)
{

	switch (state)
	{
	case WantToRunAway:
		m_AI->unschedule(schedule_selector(AI::wander));
		m_AI->setState(state);
		m_AI->getFSM()->changeState(new (std::nothrow) StateRunAway());
		m_AI->schedule(schedule_selector(AI::runAway), 0.5f);
		break;
	default:
		break;
	}
}

void StateWander::execute(AI* m_AI, EnumStateType state, Hero* target)
{
	switch (state)
	{
	case WantToTrace:
		if (m_AI->getBlood() >= target->getBlood())
		{
			m_AI->unschedule(schedule_selector(AI::wander));
			m_AI->setState(state);
			m_AI->setTarget(target);
			m_AI->getFSM()->changeState(new (std::nothrow) StateTrace());
			m_AI->schedule(schedule_selector(AI::trace), 0.5f);
			break;
		}
		else
		{
			state = WantToRunAway;
		}
	case WantToRunAway:
		m_AI->unschedule(schedule_selector(AI::wander));
		m_AI->setState(state);
		m_AI->getFSM()->changeState(new (std::nothrow) StateRunAway());
		m_AI->schedule(schedule_selector(AI::runAway), 0.5f);
		break;
	default:
		break;
	}
}
