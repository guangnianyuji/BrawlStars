#ifndef __STATE_RUN_AWAY__
#define __STATE_RUN_AWAY__

#include "State/StateTrace.h"
#include "State/StateWander.h"
#include "State/StateAttackBox.h"

class StateRunAway:public State
{
public:
	virtual void execute(AI* m_AI, EnumStateType state);

	virtual void execute(AI* m_AI, EnumStateType state, Hero* target);

	virtual void execute(AI* m_AI, EnumStateType state, Box* box);
};


#endif // !__STATE_RUN_AWAY__


