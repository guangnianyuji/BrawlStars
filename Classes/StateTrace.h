#ifndef __STATE_TRACE__
#define __STATE_TRACE__

#include"StateRunAway.h"
#include "StateWander.h"
#include "AI.h"

class StateTrace:public State
{
public:

	virtual void execute(AI* m_AI, EnumStateType state);

	virtual void execute(AI* m_AI, EnumStateType state, cocos2d::Point position);

	virtual void execute(AI* m_AI, EnumStateType state, Hero* target);
};


#endif // !__STATE_TRACE__





