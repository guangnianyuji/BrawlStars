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

	return true;
}

void FSM::changeState(State* state)
{
	CC_SAFE_DELETE(m_State);

	this->m_State = state;
}

void FSM::setMark(const std::string m_Mark)
{
	m_AIMark = m_Mark;
}

void FSM::addObservers()
{

	NotifyUtil::getInstance()->addObserver("new Hero" + m_AIMark, std::bind(&FSM::newHeroInView, this, std::placeholders::_1));

	NotifyUtil::getInstance()->addObserver("new Box" + m_AIMark, std::bind(&FSM::newBoxInView, this, std::placeholders::_1));

	NotifyUtil::getInstance()->addObserver("near Death" + m_AIMark, std::bind(&FSM::nearDeath, this, std::placeholders::_1));

	NotifyUtil::getInstance()->addObserver("being Attacked" + m_AIMark, std::bind(&FSM::injured, this, std::placeholders::_1));

	NotifyUtil::getInstance()->addObserver("hit The Enemy" + m_AIMark, std::bind(&FSM::hitTheEnemy, this, std::placeholders::_1));

	NotifyUtil::getInstance()->addObserver("hahaha" + m_AIMark, std::bind(&FSM::nothingToDo, this, std::placeholders::_1));

	NotifyUtil::getInstance()->addObserver("touching The Smog" + m_AIMark, std::bind(&FSM::touchingTheSmog, this, std::placeholders::_1));

}

void FSM::newHeroInView(Hero* target)
{

	this->m_State->execute(m_AI, WantToTrace, target);
}

void FSM::newBoxInView(Box* box)
{

	//this->m_State->execute(m_AI, WantToAttackBox, box);
}

void FSM::nearDeath(cocos2d::Ref* data)
{
	this->m_State->execute(m_AI, WantToRunAway);
}

void FSM::hitTheEnemy(Hero* target)
{
	this->m_State->execute(m_AI, WantToTrace,target);
}

void FSM::injured(Hero* target)
{
	int ran = rand() % 10 + 1;

	if (ran >= 5)
	{
		this->m_State->execute(m_AI, WantToTrace, target);
	}
	else
	{
		this->m_State->execute(m_AI, WantToRunAway);
	}

}

void FSM::nothingToDo(cocos2d::Ref* data)
{
	this->m_State->execute(m_AI, WantToWander);
}

void FSM::touchingTheSmog(cocos2d::Ref* data)
{
	this->m_State->execute(m_AI, WantToRunAway);
}


