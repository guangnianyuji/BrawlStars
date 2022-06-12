#ifndef __STATE_ATTACK_BOX__
#define __STATE_ATTACK_BOX__

#include "State/StateTrace.h"
#include "State/StateRunAway.h"
#include "State/StateWander.h"

class StateAttackBox:public State
{
	virtual void execute(AI* m_AI, EnumStateType state);

	virtual void execute(AI* m_AI, EnumStateType state, Hero* target);

	virtual void execute(AI* m_AI, EnumStateType state, Box* box);
};

#endif

