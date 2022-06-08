#include "StateRunAway.h"

void StateRunAway::execute(AI* m_AI, EnumStateType state)
{
	switch (state)
	{
	case WantToTrace:
		break;
	case WantToWander:

		m_AI->wander();
		m_AI->getFSM()->changeState(new (std::nothrow) StateWander());

		break;
	case WantToRunAway:
		break;
	default:
		break;
	}
}

void StateRunAway::execute(AI* m_AI, EnumStateType state, cocos2d::Point position)
{
	switch (state)
	{
	case WantToTrace:

		m_AI->trace(position);
		m_AI->getFSM()->changeState(new (std::nothrow) StateTrace());

		break;
	case WantToWander:
		break;
	case WantToRunAway:

		m_AI->runAway(position);
		m_AI->getFSM()->changeState(new (std::nothrow) StateRunAway());

		break;
	default:
		break;
	}
}
