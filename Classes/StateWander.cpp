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
		m_AI->setState(state);
		m_AI->getFSM()->changeState(new (std::nothrow) StateRunAway());
		break;
	default:
		break;
	}
}

void StateWander::execute(AI* m_AI, EnumStateType state, cocos2d::Point position)
{

	switch (state)
	{
	case WantToTrace:
		m_AI->setState(state);
		m_AI->setBoxPosition(position);
		m_AI->getFSM()->changeState(new (std::nothrow) StateTrace());
		break;
	case WantToWander:
		m_AI->setState(state);
		m_AI->getFSM()->changeState(new (std::nothrow) StateWander());
		break;
	case WantToRunAway:
		m_AI->setState(state);
		m_AI->getFSM()->changeState(new (std::nothrow) StateRunAway());
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
		m_AI->setState(state);
		m_AI->setTarget(target);
		m_AI->getFSM()->changeState(new (std::nothrow) StateTrace());
	default:
		break;
	}
}
