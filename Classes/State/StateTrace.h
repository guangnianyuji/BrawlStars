#ifndef __STATE_TRACE__
#define __STATE_TRACE__

#include"StateRunAway.h"
#include "State/StateWander.h"
#include "State/StateAttackBox.h"
#include "Entity/Hero/AI.h"

class StateTrace:public State
{
public:

	virtual void execute(AI* m_AI, EnumStateType state);

	virtual void execute(AI* m_AI, EnumStateType state, Hero* target);

	virtual void execute(AI* m_AI, EnumStateType state, Box* box);
};


#endif // !__STATE_TRACE__





