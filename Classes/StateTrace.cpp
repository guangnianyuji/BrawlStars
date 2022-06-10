#include "StateTrace.h"

void StateTrace::execute(AI* m_AI, EnumStateType state)
{
	switch (state)
	{
	case WantToWander:
		m_AI->unschedule(schedule_selector(AI::trace));
		m_AI->setState(state);
		m_AI->getFSM()->changeState(new (std::nothrow) StateWander());
		m_AI->schedule(schedule_selector(AI::wander), 0.5f);
		break;
	default:
		break;
	}
}

void StateTrace::execute(AI* m_AI, EnumStateType state, Hero* target)
{
	switch (state)
	{
	case WantToTrace:
		if (target == m_AI->getTarget())
		{

		}
		else if (target->getBlood() < m_AI->getTarget()->getBlood())
		{
			m_AI->setState(state);
			m_AI->setTarget(target);
			m_AI->getFSM()->changeState(new (std::nothrow) StateTrace());
		}
		break;
	default:
		break;
	}
}

void StateTrace::execute(AI* m_AI, EnumStateType state, Box* box)
{
	switch (state)
	{
	case WantToAttackBox:
		if (m_AI->getTarget()->getBlood() <= m_AI->getBlood() * 0.5)
		{
			break;
		}
		else
		{
			m_AI->unschedule(schedule_selector(AI::trace));
			m_AI->setState(state);
			m_AI->setBox(box);
			m_AI->getFSM()->changeState(new (std::nothrow) StateAttackBox());
			m_AI->schedule(schedule_selector(AI::attackBox), 0.5f);
		}
		break;
	default:
		break;
	}
}
