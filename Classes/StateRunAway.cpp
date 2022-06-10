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

void StateRunAway::execute(AI* m_AI, EnumStateType state, Box* box)
{
	switch (state)
	{
	case WantToAttackBox:
		m_AI->unschedule(schedule_selector(AI::runAway));
		m_AI->setState(state);
		m_AI->setBox(box);
		m_AI->getFSM()->changeState(new (std::nothrow) StateAttackBox());
		m_AI->schedule(schedule_selector(AI::attackBox), 1.0f);
	default:
		break;
	}
}
