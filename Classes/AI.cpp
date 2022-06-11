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

	schedule(schedule_selector(AI::wander),30.0/this->getSpeed());

	return true;
}

void AI::setPhyBody()
{
	/* ʹAI����������������� */
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

	/* ���еĳ���ʱ���Ѿ���ȥ�� */
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

void AI::setState(EnumStateType state)
{
	stepForAttackBox = 0;
	stepForRunAway = 0;
	stepForTrace = 0;
	stepForWander = 0;

	m_State = state;
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

	runAction(MoveTo::create(30.0/this->getSpeed(), endPosition));

	m_isMoving = true;
}

/* AI����׷��ģʽ */
void AI::trace(float delta)
{
	
	if (m_State != WantToTrace)
		return;
	/* ���Ŀ���Ѿ��������л�״̬ */
	if (this->getTarget()->isDead())
	{
		NotifyUtil::getInstance()->postNotification("hahaha" + this->getFSM()->getMark(), (Ref*)"hahaha");

		/* ��Ŀ���λ������Ϊԭ�㣬��ʾû��׷��Ŀ�� */
		this->m_TargetPosition = Vec2(0, 0);
	}

	/* ����Ǹտ�ʼ׷�ٻ�����Ŀ�����Լ�̫Զ�ˣ������¼���·�� */
	if (this->m_TargetPosition==Vec2(0,0) ||
			this->getTarget()->getPosition().distance(m_TargetPosition)>50.0f)
	{
		m_TargetPosition = this->getTarget()->getPosition();

		/* ע�����¼��㲽�� */
		stepForTrace = 0;

		/* �Ҳ���·�����л�״̬ */
		if (!PathFinding::getInstance()->AStarInArea(this->getPosition(), this->getTarget()->getPosition(), Path))
		{
			NotifyUtil::getInstance()->postNotification("hahaha" + this->getFSM()->getMark(), (Ref*)"hahaha");
		}

	}

	if (stepForTrace >= 0 && stepForTrace < Path.size())
	{
		move(Path[Path.size() - 1 - stepForTrace], this->getSpeed());
		stepForTrace++;

	}	
	float Angle = MathUtils::getRad(this->getPosition(), m_Target->getPosition());

	this->updateNormalAttackState();
	if (getNormalAttackState())
	{
		this->normalAttack(Angle);
		if (!this->getACE_CD_State())
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

	if (stepForTrace == Path.size() - 1)
	{
		if(m_Target->getBlood()>this->getBlood())
			NotifyUtil::getInstance()->postNotification("being Attacked" + this->getFSM()->getMark(), this->getTarget());
	}

}

void AI::runAway(float delta)
{
	if (m_State == WantToRunAway && stepForRunAway == 0)
	{
		int x = rand() % 500 + 1;

		int y = rand() % 500 + 1;

		Point endPosition = this->getPosition();
		endPosition.x += x;
		endPosition.y += y;

		if (!PathFinding::getInstance()->AStarInArea(this->getPosition(), endPosition, Path))
		{
			NotifyUtil::getInstance()->postNotification("hahaha" + this->getFSM()->getMark(), (Ref*)"hahaha");
		}
	}
	if (m_State != WantToRunAway)
		return;
	if (stepForRunAway >= 0 && stepForRunAway < Path.size())
	{
		move(Path[Path.size() - 1 - stepForRunAway], this->getSpeed());
		stepForRunAway++;
	}
	if (stepForRunAway == Path.size())
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

			NotifyUtil::getInstance()->postNotification("hahaha" + this->getFSM()->getMark(), (Ref*)"hahaha");
		}
	}
	if (m_State != WantToWander)
		return;

	if (stepForWander >= 0 && stepForWander < Path.size())
	{
		move(Path[Path.size() - 1 - stepForWander], this->getSpeed());
		stepForWander++;
	}
	
	if (stepForWander == Path.size())
	{
		stepForWander = 0;
		NotifyUtil::getInstance()->postNotification("hahaha" + this->getFSM()->getMark(), (Ref*)"hahaha");
	}
}

void AI::attackBox(float delta)
{
	if (m_State != WantToAttackBox)
		return;

	float Angle;

	/* �ոտ�ʼ�����˱��� */
	if (this->m_BoxPosition==Vec2(0,0))
	{
		Angle = Pi / (rand() % 6 + 1);

		m_BoxPosition = this->getBox()->getPosition();

		Point endPosition = m_BoxPosition;


		/* �Ҳ���·�����л�״̬ */
		if (!PathFinding::getInstance()->AStarInArea(this->getPosition(), endPosition, Path))
		{
			NotifyUtil::getInstance()->postNotification("hahaha" + this->getFSM()->getMark(), (Ref*)"hahaha");
		}
	}

	/* �ñ����Ѿ��ı�λ�ã�˵������������ */
	if (m_BoxPosition != this->getBox()->getPosition())
	{
		stepForAttackBox = 0;

		m_BoxPosition = Vec2(0, 0);

		/* �л�״̬ */
		NotifyUtil::getInstance()->postNotification("hahaha" + this->getFSM()->getMark(), (Ref*)"hahaha");
	}

	if (stepForAttackBox >=0 && stepForAttackBox <Path.size())
	{
		move(Path[Path.size() - 1 - stepForAttackBox], this->getSpeed());
		stepForAttackBox++;

		//if (this->getPosition().distance(m_BoxPosition) <= m_Character.m_Range)
		//{
		//	this->updateNormalAttackState();                                  
		//	if (getNormalAttackState())
		//	{
		//		Angle = MathUtils::getRad(this->getPosition(), m_BoxPosition);
		//		this->normalAttack(Angle);
		//		if (!this->getACE_CD_State())
		//			this->addCount();
		//	}
		//}
	}

	/* �Ѿ��ߵ����丽���� */
	if (stepForAttackBox == Path.size())
	{

		this->updateNormalAttackState();
		if (getNormalAttackState())
		{
			Angle = MathUtils::getRad(this->getPosition(), m_BoxPosition);
			this->normalAttack(Angle);
			if (!this->getACE_CD_State())
				this->addCount();
		}

	}
}

