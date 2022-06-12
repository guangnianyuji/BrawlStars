#ifndef __STATE_WANDER__
#define __STATE_WANDER__

#include "Entity/Hero/AI.h"
#include "State/StateRunAway.h"
#include "State/StateTrace.h"
#include "State/StateAttackBox.h"
#include "cocos2d.h"

class StateWander:public State
{
public:
	virtual void execute(AI* m_AI, EnumStateType state);

	virtual void execute(AI* m_AI, EnumStateType state, Hero* target);

	virtual void execute(AI* m_AI, EnumStateType state, Box* box);
};

#endif

