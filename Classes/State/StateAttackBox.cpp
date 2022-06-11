#include "StateAttackBox.h"

void StateAttackBox::execute(AI* m_AI, EnumStateType state)
{
	switch (state)
	{
	case WantToWander:
		m_AI->unschedule(schedule_selector(AI::attackBox));
		m_AI->setState(state);
		m_AI->getFSM()->changeState(new (std::nothrow) StateWander());
		m_AI->schedule(schedule_selector(AI::wander), 30.0/m_AI->getSpeed());
		break;
	case WantToRunAway:
		m_AI->unschedule(schedule_selector(AI::attackBox));
		m_AI->setState(state);
		m_AI->getFSM()->changeState(new (std::nothrow) StateRunAway());
		m_AI->schedule(schedule_selector(AI::runAway), 30.0/m_AI->getSpeed());
		break;
	default:
		break;
	}
}

void StateAttackBox::execute(AI* m_AI, EnumStateType state, Hero* target)
{
	switch (state)
	{
	case WantToTrace:
		if (m_AI == nullptr || target == nullptr)
			break;
		if (m_AI->getBlood() >= target->getBlood())
		{
			m_AI->unschedule(schedule_selector(AI::attackBox));
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
		break;
	case WantToRunAway:
		m_AI->unschedule(schedule_selector(AI::attackBox));
		m_AI->setState(state);
		m_AI->getFSM()->changeState(new (std::nothrow) StateRunAway());
		m_AI->schedule(schedule_selector(AI::runAway), 30.0/m_AI->getSpeed());
		break;
	default:
		break;
	}
}

void StateAttackBox::execute(AI* m_AI, EnumStateType state, Box* box)
{
	switch (state)
	{		   
		if (m_AI == nullptr)
			break;
	case WantToAttackBox:
		if (m_AI->getBlood() <= m_AI->m_Character.m_BloodVolume * 0.1)
		{
			state = WantToRunAway;
		}
		else
		{
			break;
		}
	case WantToRunAway:
		m_AI->unschedule(schedule_selector(AI::attackBox));
		m_AI->setState(state);
		m_AI->getFSM()->changeState(new (std::nothrow) StateRunAway());
		m_AI->schedule(schedule_selector(AI::runAway), 30.0/m_AI->getSpeed());
		break;
	default:
		break;
	}
}
