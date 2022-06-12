#include "State/StateRunAway.h"

void StateRunAway::execute(AI* m_AI, EnumStateType state)
{
	switch (state)
	{
	case WantToWander:
		m_AI->unschedule(schedule_selector(AI::runAway));
		m_AI->setState(state);
		m_AI->getFSM()->changeState(new (std::nothrow) StateWander());
		m_AI->schedule(schedule_selector(AI::wander),30.0/m_AI->getSpeed());
		break;
	case WantToRunAway:
		m_AI->unschedule(schedule_selector(AI::runAway));
		m_AI->setState(state);
		m_AI->getFSM()->changeState(new (std::nothrow) StateWander());
		m_AI->schedule(schedule_selector(AI::runAway), 30.0 / m_AI->getSpeed());
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
		m_AI->schedule(schedule_selector(AI::trace), 30.0/m_AI->getSpeed());
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
		m_AI->schedule(schedule_selector(AI::attackBox), 30.0/m_AI->getSpeed());
	default:
		break;
	}
}
