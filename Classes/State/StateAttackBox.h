#ifndef __STATE_ATTACK_BOX__
#define __STATE_ATTACK_BOX__

#include "StateTrace.h"
#include "StateRunAway.h"
#include "StateWander.h"

class StateAttackBox:public State
{
	virtual void execute(AI* m_AI, EnumStateType state);

	virtual void execute(AI* m_AI, EnumStateType state, Hero* target);

	virtual void execute(AI* m_AI, EnumStateType state, Box* box);
};

#endif

