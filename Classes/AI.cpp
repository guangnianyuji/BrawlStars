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

void AI::wander()
{
	/*if (!Path.empty())
		Path.clear();

	int x = 10 + rand() % 100;
	int y = 10 + rand() % 100;

	Point endposition = this->getPosition();

	endposition.x += x;
	endposition.y += y;

	float Angle = MathUtils::getRad(this->getPosition(), endposition);

	this->beganToMove(Angle, this->getSpeed(), endposition);*/
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
		
	switch (m_State)
	{
	case WantToTrace:
		trace(m_Target->getPosition());
		break;
	case WantToRunAway:
		runAway(this->getPosition());
		break;
	case WantToWander:
		wander();
		break;
	default:
		break;
	}
}

void AI::findPath()
{
	if (m_FindPathThread == nullptr)
	{
		m_FindPathThread = new std::thread(&AI::findPathAsync, this);
		auto scheduler = Director::getInstance()->getScheduler();
		scheduler->schedule(schedule_selector(AI::asynsUpdate), this, 0, false);
	}
}

void AI::findPathAsync()
{
	PathFinding::getInstance()->AStarInArea(this->startPosition, this->endPosition, this->Path);
}

void AI::asynsUpdate(float delta)
{
	if (!Path.empty())
	{
		auto scheduler = cocos2d::Director::getInstance()->getScheduler();
		scheduler->unschedule(schedule_selector(AI::asynsUpdate), this);

		m_FindPathThread->join();
		CC_SAFE_DELETE(m_FindPathThread);
	}
}

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

void AI::trace(cocos2d::Point position)
{
	//this->endPosition = position;
	//this->startPosition = this->getPosition();
	//findPath();

	//if (Path[0]!=Vec2(0,0))
	//{
	//	for (int ix = Path.size()-1, cnt = 0; ix>=0 && cnt <= 1000; ix--, cnt++)
	//	{
	//		if (ix!=Path.size()-1 && this->getPosition() != Path[ix + 1])
	//		{
	//			ix++;
	//		}
	//		Point positon = Path[ix];
	//		float Angle = MathUtils::getRad(this->getPosition(), position);

	//		this->beganToMove(Angle, this->getSpeed()/50, position);

	//		/* 手动更新攻击状态 */
	//		this->updateNormalAttackState();
	//		if (getNormalAttackState())
	//		{
	//			this->normalAttack(Angle);
	//			this->addCount();
	//		}

	//		if (this->getACE_CD_State())
	//		{
	//			this->updateACEState();
	//			if (this->getACEState())
	//			{
	//				this->ACE(Angle);
	//			}
	//		}
	//	}
	//}
	//float dis = (this->getPosition()).distance(position);
	//if (dis >= 200.0f) return;

	float Angle = MathUtils::getRad(this->getPosition(), position);
	this->beganToMove(Angle, this->getSpeed(), position);

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

void AI::runAway(cocos2d::Point position)
{

	int nowArea = this->getArea();
	int nextArea=nowArea;

	if (nowArea + 1 >= 1 && nowArea + 1 <= 9)
	{
		nextArea = nowArea + 1;
	}
	else
	{
		nextArea = nowArea - 1;
	}

	m_Waypoint waypoint = PathFinding::getInstance()->findWayPointInArea(nextArea);

	if (PathFinding::getInstance()->AStarInArea(this->getPosition(), waypoint.position, Path))

	m_Waypoint waypoint = PathFinding::getInstance()->findWayPointInArea(nextArea);

	//this->startPosition = this->getPosition();
	//this->endPosition = waypoint.position;

	//findPath();

	if (Path[0] != Vec2(0, 0))
	{

	}

}

