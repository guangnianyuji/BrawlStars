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

	return fsm;
}

bool FSM::initWithAI(AI* m_AI)
{

	this->m_AI = m_AI;

	NotifyUtil::getInstance()->addObserver("new Hero", std::bind(&FSM::newHeroInView,this,std::placeholders::_1));

	NotifyUtil::getInstance()->addObserver("new Box", std::bind(&FSM::newBoxInView, this, std::placeholders::_1));

	NotifyUtil::getInstance()->addObserver("hit the Enemy", std::bind(&FSM::hitTheEnemy, this, std::placeholders::_1));

}

void FSM::changeState(State* state)
{
	CC_SAFE_DELETE(m_State);

	this->m_State = state;
}

void FSM::newHeroInView(cocos2d::Point position)
{
	float RealTimeBlood = m_AI->m_Blood->getRealTimeBlood();

	float BloodVolume = m_AI->m_Blood->getBloodVolume();

	int ran = rand() % 10;

	if (RealTimeBlood >= BloodVolume * 0.7)
	{
		if (ran >= 7)
		{

		}
		else
		{

		}
	}
	else if (RealTimeBlood > BloodVolume * 0.4 && RealTimeBlood < BloodVolume * 0.7)
	{
		if (ran >= 6)
		{

		}
		else
		{

		}
	}
	else
	{

	}
}

void FSM::newBoxInView(cocos2d::Point position)
{
	float RealTimeBlood = m_AI->m_Blood->getRealTimeBlood();

	float BloodVolume = m_AI->m_Blood->getBloodVolume();

	int ran = rand() % 10;

	if (RealTimeBlood  >= BloodVolume * 0.5)
	{
		//в╥вы
	}
}

void FSM::nearDeath(cocos2d::Ref* data)
{
	//лсеэ
}

void FSM::hitTheEnemy(cocos2d::Point position)
{
	float RealTimeBlood = m_AI->m_Blood->getRealTimeBlood();

	float BloodVolume = m_AI->m_Blood->getBloodVolume();

	int ran = rand() % 10;

	if (RealTimeBlood >= BloodVolume * 0.5)
	{
		//в╥вы
	}
	else
	{
		//лсеэ
	}
}

void FSM::injured(cocos2d::Point position)
{
	float RealTimeBlood = m_AI->m_Blood->getRealTimeBlood();

	float BloodVolume = m_AI->m_Blood->getBloodVolume();

	int ran = rand() % 10;

	if (RealTimeBlood >= BloodVolume * 0.7)
	{
		//в╥вы
	}
	else
	{
		//лсеэ
	}
}


