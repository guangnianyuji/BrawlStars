#ifndef __STATE__
#define __STATE__

#include "cocos2d.h"
#include "EnumStateType.h"

class AI;

class State
{
public:
	virtual void execute(AI* m_AI, EnumStateType state) = 0;

	virtual void execute(AI* m_AI, EnumStateType state,cocos2d::Point position) = 0;
};

#endif // !__STATE__




