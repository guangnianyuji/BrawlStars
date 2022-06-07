#ifndef __STATE_WANDER__
#define __STATE_WANDER__

#include "AI.h"
#include "StateRunAway.h"
#include "StateTrace.h"

class StateWander:public State
{
public:
	virtual void execute(AI* m_AI, EnumStateType state);

	virtual void execute(AI* m_AI, EnumStateType state, cocos2d::Point position);
};

#endif

