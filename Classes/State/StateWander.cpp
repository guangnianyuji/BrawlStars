#include "State/StateWander.h"

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
		m_AI->schedule(schedule_selector(AI::runAway), 30.0/m_AI->getSpeed());
	default:
		break;
	}
}

void StateWander::execute(AI* m_AI, EnumStateType state, Hero* target)
{
	switch (state)
	{
	case WantToTrace:
		if (m_AI == nullptr || target == nullptr)
			break;
		if (m_AI->getBlood() +100.0f >= target->getBlood())
		{
			m_AI->unschedule(schedule_selector(AI::wander));
			m_AI->setState(state);
			m_AI->setTarget(target);
			m_AI->getFSM()->changeState(new (std::nothrow) StateTrace());
			m_AI->schedule(schedule_selector(AI::trace), 30.0/m_AI->getSpeed());
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
		m_AI->schedule(schedule_selector(AI::runAway), 30.0/m_AI->getSpeed());
		break;
	default:
		break;
	}
}

void StateWander::execute(AI* m_AI, EnumStateType state, Box* box)
{
	switch (state)
	{
	case WantToAttackBox:
		if (m_AI == nullptr)
			break;

		if (m_AI->getBlood() <= m_AI->m_Character.m_BloodVolume * 0.1)
		{
			state = WantToRunAway;
		}
		else
		{
			m_AI->unschedule(schedule_selector(AI::wander));
			m_AI->setState(state);
			m_AI->setBox(box);
			m_AI->getFSM()->changeState(new (std::nothrow) StateAttackBox());
			m_AI->schedule(schedule_selector(AI::attackBox), 30.0/m_AI->getSpeed());
			break;
		}
	case WantToRunAway:
		m_AI->unschedule(schedule_selector(AI::wander));
		m_AI->setState(state);
		m_AI->getFSM()->changeState(new (std::nothrow) StateRunAway());
		m_AI->schedule(schedule_selector(AI::runAway), 30.0/m_AI->getSpeed());
		break;
	default:
		break;
	}
}
