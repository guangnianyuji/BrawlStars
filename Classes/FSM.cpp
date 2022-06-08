#include "FSM.h"

FSM::~FSM()
{
	//NotifyUtil::getInstance()->removeObserver(this);
}

FSM* FSM::createWithAI(AI* m_AI)
{
	FSM* fsm = new FSM();

	if (fsm && fsm->initWithAI(m_AI))
	{
		fsm->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(fsm);

		fsm = nullptr;
	}

	return fsm;
}

bool FSM::initWithAI(AI* m_AI)
{

	this->m_AI = m_AI;

	this->m_State = nullptr;

	NotifyUtil::getInstance()->addObserver("new Hero", std::bind(&FSM::newHeroInView,this,std::placeholders::_1));

	NotifyUtil::getInstance()->addObserver("new Box", std::bind(&FSM::newBoxInView, this, std::placeholders::_1));

	NotifyUtil::getInstance()->addObserver("near Death", std::bind(&FSM::nearDeath, this, std::placeholders::_1));

	NotifyUtil::getInstance()->addObserver("being Attacked", std::bind(&FSM::injured, this, std::placeholders::_1));

	NotifyUtil::getInstance()->addObserver("hit The Enemy", std::bind(&FSM::hitTheEnemy, this, std::placeholders::_1));

	return true;
}

void FSM::changeState(State* state)
{
	CC_SAFE_DELETE(m_State);

	this->m_State = state;
}

void FSM::newHeroInView(cocos2d::Point position)
{

	int ran = rand() % 10;

	if (ran >= 3)
	{
			this->m_State->execute(m_AI, WantToTrace, position);
	}
	else
	{
			this->m_State->execute(m_AI, WantToRunAway, position);
	}
}

void FSM::newBoxInView(cocos2d::Point position)
{

	this->m_State->execute(m_AI, WantToTrace, position);
}

void FSM::nearDeath(cocos2d::Ref* data)
{
	this->m_State->execute(m_AI, WantToRunAway, this->getPosition());
}

void FSM::hitTheEnemy(cocos2d::Point position)
{

	this->m_State->execute(m_AI, WantToTrace, position);

}

void FSM::injured(cocos2d::Point position)
{

	this->m_State->execute(m_AI, WantToTrace, position);
}


