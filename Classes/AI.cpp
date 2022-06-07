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
	if (!Path.empty())
		Path.clear();

	int x = rand() % 100;
	int y = rand() % 100;

	Point endposition = this->getPosition();

	endposition.x += x;
	endposition.y += y;

	if (!PathFinding::getInstance()->isNotSafety(MathUtils::PositionToTiled(endposition, (TMXTiledMap*)this->getParent())))
	{
		if (PathFinding::getInstance()->AStarInArea(this->getPosition(), endposition, Path))
		{
			for (int ix = 0, cnt = 0; ix <= Path.size() - 1 && cnt <= 100; ix++, cnt++)
			{
				if (ix && this->getPosition() != Path[ix - 1])
				{
					ix--;
				}

				float Angle = MathUtils::getRad(this->getPosition(), Path[ix]);

				this->beganToMove(Angle, this->getSpeed(), endposition);


				/* 判断是否已经移动出了当前区域，如果是，则发布通知 */
				if (this->getArea() != PathFinding::getInstance()->findArea(this->getPosition()))
				{
					this->setArea(PathFinding::getInstance()->findArea(this->getPosition()));

					NotifyUtil::getInstance()->postNotification("new Hero", this->getPosition());
				}
			}
		}
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
	this->addChild(m_FSM);
	//this->getFSM()->changeState(new StateWander());

	m_TimeCounter = TimeCounter::create();
	this->addChild(m_TimeCounter);
	m_TimeCounter->startCounting();

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
	if (!Path.empty())
		Path.clear();

	if (PathFinding::getInstance()->AStarInArea(this->getPosition(), position,Path))
	{
		for (int ix = 0,cnt=0; ix <= Path.size() - 1&&cnt<=100; ix++,cnt++)
		{
			if (ix && this->getPosition() != Path[ix - 1])
			{
				ix--;
			}

			float Angle = MathUtils::getRad(this->getPosition(), Path[ix]);

			this->beganToMove(Angle, this->getSpeed(), position);


			/* 判断是否已经移动出了当前区域，如果是，则发布通知 */
			if (this->getArea() != PathFinding::getInstance()->findArea(this->getPosition()))
			{
				this->setArea(PathFinding::getInstance()->findArea(this->getPosition()));

				NotifyUtil::getInstance()->postNotification("new Hero", this->getPosition());
			}

			/* 手动更新攻击状态 */
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
	}
}

void AI::runAway(cocos2d::Point position)
{
	if (!Path.empty())
		Path.clear();

	int nowArea = this->getArea();
	int nextArea;

	if (nowArea + 1 >= 1 && nowArea <= 9)
	{
		nextArea = nowArea + 1;
	}
	else
	{
		nextArea + nowArea - 1;
	}

	m_Waypoint waypoint = PathFinding::getInstance()->findWayPointInArea(nextArea);

	if (PathFinding::getInstance()->AStarInArea(this->getPosition(), waypoint.position, Path))
	{
		for (int ix = 0, cnt = 0; ix <= Path.size() - 1 && cnt <= 100; ix++, cnt++)
		{
			if (ix && this->getPosition() != Path[ix - 1])
			{
				ix--;
			}

			float Angle = MathUtils::getRad(this->getPosition(), Path[ix]);

			this->beganToMove(Angle, this->getSpeed(), position);


			/* 判断是否已经移动出了当前区域，如果是，则发布通知 */
			if (this->getArea() != PathFinding::getInstance()->findArea(this->getPosition()))
			{
				this->setArea(PathFinding::getInstance()->findArea(this->getPosition()));

				NotifyUtil::getInstance()->postNotification("new Hero", this->getPosition());
			}
		}
}

