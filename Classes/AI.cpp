#include "AI.h"

AI* AI::create(Character character)
{
	AI* pRet = new(std::nothrow) AI();
	pRet->m_Character = character;

	if (pRet && pRet->init()) {
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}


bool AI::init()
{
	if (!Hero::init())
	{
		return false;
	}

	setPhyBody();



	m_FSM = FSM::createWithAI(this);
	m_FSM->retain();
	this->getFSM()->changeState(new StateWander());

	this->setState(WantToWander);

	m_TimeCounter = TimeCounter::create();
	this->addChild(m_TimeCounter);
	m_TimeCounter->startCounting();


	m_FindPathThread = nullptr;
	this->scheduleUpdate();

	schedule(schedule_selector(AI::wander), 0.50f);

	return true;
}

void AI::setPhyBody()
{
	/* 使AI的身体承载物理属性 */
	auto physicsBody = PhysicsBody::createBox(m_Body->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setGravityEnable(false);
	physicsBody->setCategoryBitmask(0x0001);
	physicsBody->setCollisionBitmask(0x0001);
	physicsBody->setContactTestBitmask(0x0001);
	this->setPhysicsBody(physicsBody);

}

void AI::updateACE_CD_State()
{
	if (m_Count >= m_Character.m_Count)
	{
		m_StartACETime = m_TimeCounter->getTime();
		setACE_CD_State(true);
		m_Count = 0;
	}

	/* 绝招的持续时间已经过去了 */
	if (m_TimeCounter->getTime() - m_StartACETime >= m_Character.m_Duration)
	{
		m_StartACETime = 0;
		setACE_CD_State(false);
	}
}

void AI::update(float delta)
{
	updateACE_CD_State();

	if (!getACE_CD_State())
	{
		if (this->damageImmunity())
			this->stopACE();

		if (this->getSpeed() != this->m_Character.m_Speed)
			this->stopACE();
	}
}

//void AI::findPath()
//{
//	if (m_FindPathThread == nullptr)
//	{
//		m_FindPathThread = new std::thread(&AI::findPathAsync, this);
//		auto scheduler = Director::getInstance()->getScheduler();
//		scheduler->schedule(schedule_selector(AI::asynsUpdate), this, 0, false);
//	}
//}
//
//void AI::findPathAsync()
//{
//	//PathFinding::getInstance()->AStarInArea(this->startPosition, this->endPosition, this->Path);
//}
//
//void AI::asynsUpdate(float delta)
//{
//	if (!Path.empty())
//	{
//		auto scheduler = cocos2d::Director::getInstance()->getScheduler();
//		scheduler->unschedule(schedule_selector(AI::asynsUpdate), this);
//
//		m_FindPathThread->join();
//		CC_SAFE_DELETE(m_FindPathThread);
//	}
//}

void AI::updateACEState()
{
	float delta = m_TimeCounter->getTime() - m_LastACETime;

	if (delta >= m_Character.m_ACEIntervalTime || !m_LastACETime)
	{
		m_LastACETime = m_TimeCounter->getTime();
		m_ACEState = true;
	}
	else
	{
		m_ACEState = false;
	}
}

void AI::updateNormalAttackState()
{
	float delta = m_TimeCounter->getTime() - m_LastNormalAttackTime;
	if (delta >= m_Character.m_IntervalTime || (!m_LastNormalAttackTime))
	{
		m_LastNormalAttackTime = m_TimeCounter->getTime();
		m_NormalAttackState = true;
	}
	else
	{
		m_NormalAttackState = false;
	}
}

void AI::move(Point endPosition, float speed)
{
	float Angle = MathUtils::getRad(this->getPosition(), endPosition);

	if (this == nullptr)
		return;
	if (this->getPosition() == endPosition)
		return;
	std::string tempDirection;
	if (Angle > -3 * Pi / 4 && Angle < -Pi / 4)
	{
		tempDirection = "f";
	}
	else if (Angle < 3 * Pi / 4 && Angle > Pi / 4)
	{
		tempDirection = "b";
	}
	else if (Angle > 3 * Pi / 4 || Angle < -3 * Pi / 4)
	{
		tempDirection = "l";
	}
	else if (Angle > -Pi / 4 && Angle < 3 * Pi / 4)
	{
		tempDirection = "r";
	}
	if (tempDirection != m_Direction)
	{
		m_Direction = tempDirection;
		m_Body->stopAllActions();
		m_Body->runAction(AnimationUtils::createAnimation(m_Character.m_Name, m_Direction));
	}

	runAction(MoveTo::create(0.5f, endPosition));

	m_isMoving = true;
}

void AI::trace(float delta)
{
	if (this->m_State != WantToTrace)
		return;

	float Angle = MathUtils::getRad(this->getPosition(), m_Target->getPosition());

	Point position = m_Target->getPosition() - MathUtils::getVectorialSpeed(Angle, m_Character.m_Range);

	move( position,this->getSpeed());

	this->updateNormalAttackState();
	if (getNormalAttackState())
	{
		this->normalAttack(Angle);
		this->addCount();
	}

	if (this->getACE_CD_State())
	{
		this->updateACEState();
		if (this->getACEState())
		{
			this->ACE(Angle);
		}
	}
}

void AI::runAway(float delta)
{
	if (m_State == WantToRunAway && stepForRunAway == 0)
	{
		if (!PathFinding::getInstance()->AStarInArea(this->getPosition(),
			PathFinding::getInstance()->findWayPointInArea((this->getArea() + 1) % 9).position, Path))
		{
			NotifyUtil::getInstance()->postNotification("hahaha" + this->getFSM()->getMark(), (Ref*)"hahaha");
		}
	}
	if (m_State != WantToRunAway)
		return;
	move(Path[Path.size() - 1-stepForRunAway], this->getSpeed());
	stepForRunAway++;
	if (stepForRunAway == Path.size() - 2)
	{
		stepForRunAway = 0;
		NotifyUtil::getInstance()->postNotification("hahaha" + this->getFSM()->getMark(), (Ref*)"hahaha");
	}
}

void AI::wander(float delta)
{
	if (m_State == WantToWander && stepForWander == 0)
	{
		Point endPosition = MathUtils::TiledToPosition(Point(30, 30), (TMXTiledMap*)this->getParent());

		if (!PathFinding::getInstance()->AStarInArea(this->getPosition(),endPosition, Path))
		{
			
		}
	}
	if (m_State != WantToWander)
		return;
	move(Path[Path.size() - 1 - stepForWander], this->getSpeed());
	stepForWander++;
	if (stepForWander == Path.size() - 2)
	{
		stepForWander = 0;
		NotifyUtil::getInstance()->postNotification("hahaha" + this->getFSM()->getMark(), (Ref*)"hahaha");
	}
}

