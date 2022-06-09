#include "StateRunAway.h"

void StateRunAway::execute(AI* m_AI, EnumStateType state)
{
	switch (state)
	{
	case WantToWander:
		m_AI->unschedule(schedule_selector(AI::runAway));
		m_AI->setState(state);
		m_AI->getFSM()->changeState(new (std::nothrow) StateWander());
		m_AI->schedule(schedule_selector(AI::wander),0.5f);
		break;
	default:
		break;
	}
}

void StateRunAway::execute(AI* m_AI, EnumStateType state, cocos2d::Point position)
{
	switch (state)
	{
	case WantToRunAway:
		break;
	default:
		break;
	}
}

void StateRunAway::execute(AI* m_AI, EnumStateType state, Hero* target)
{
	switch (state)
	{
	case WantToTrace:
		m_AI->unschedule(schedule_selector(AI::runAway));
		m_AI->setState(state);
		m_AI->setTarget(target);
		m_AI->getFSM()->changeState(new (std::nothrow) StateTrace());
		m_AI->schedule(schedule_selector(AI::trace), 0.5f);
	default:
		break;
	}
}
