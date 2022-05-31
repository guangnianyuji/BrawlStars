#include "FightScene.h"


FightScene* FightScene::create(Character character)
{
	FightScene* pRet = new(std::nothrow)FightScene();

	Vec2 VisibleSize = Director::getInstance()->getVisibleSize();

	pRet->m_TiledMap = TMXTiledMap::create("map.tmx");

	pRet->m_Player = Player::create(character);


	if (pRet && pRet->init())
	{
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

bool FightScene::init()
{

	if (!Scene::initWithPhysics())
	{
		return false;
	}

	if (!BaseScene::init())
	{
		return false;
	}
	Vec2 VisibleSize = Director::getInstance()->getVisibleSize();

	//加入地图
	addChild(m_TiledMap,-1);

	//获取障碍层
	m_WallLayer = m_TiledMap->layerNamed("wall");//获取需要添加PhysicsBody的瓦片所在的图层
	Size TiledNumber = m_TiledMap->getMapSize();

	//设置玩家初始位置
	m_Player->setOriginalPositionInMap(m_TiledMap,"PlayerBirthPlace");

	//将玩家加入到地图中
	m_TiledMap->addChild(m_Player,4);

	m_FightControllerLayer = FightControllerLayer::create(Vec2(VisibleSize.x / 4, VisibleSize.y / 3));

		
	//在场景中加入遥杆
	m_FightControllerLayer->startMoveRocker(true);

	//开启场景碰撞监听
	startContactListen();

	//为玩家节点设置名字，方便之后的碰撞检测
	m_Player->setName("Person");	

	addChild(m_FightControllerLayer,2);


	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	m_TimeCounter = TimeCounter::create();

	addChild(m_TimeCounter);

	m_TimeCounter->startCounting();


	scheduleUpdate();
	
	return true;
}

void FightScene::update(float delta)
{
	updatePlayerMove();
	updateViewPointByPlayer();
	updatePlayerAttack(m_TimeCounter->getTime());

}

void FightScene::updateViewPointByPlayer()
{
	//地图方块数量
	Size TiledNumber = m_TiledMap->getMapSize();

	//地图单个格子大小
	Size TiledSize = m_TiledMap->getTileSize();

	//地图大小
	Size TiledMapSize = Size(TiledNumber.width * TiledNumber.width,
		TiledNumber.height * TiledNumber.height);

	//屏幕大小
	Size VisibleSize = Director::getInstance()->getVisibleSize();

	//获取主角坐标
	Point PlayerPosition = m_Player->getPosition();

	//获取坐标
	float x = std::max(PlayerPosition.x, VisibleSize.width/ 2);
	float y = std::max(PlayerPosition.y,VisibleSize.height / 2);

	//如果 x,y坐标大于右上角的极限值，则取极限值的坐标
	x = std::min(x, TiledMapSize.width - VisibleSize.width / 2);
	y = std::min(y, TiledMapSize.height - VisibleSize.height/ 2);

	Point DestinationPosition = Point(x, y);

	Point CenterPosition = VisibleSize / 2;

	m_TiledMap->setPosition(CenterPosition - DestinationPosition);
}


Vec2 FightScene::PositionToTiled(const Vec2& position)
{
	int x = position.x / m_TiledMap->getTileSize().width;

	int y = ((m_TiledMap->getMapSize().height * m_TiledMap->getTileSize().height) - position.y) /
		m_TiledMap->getTileSize().height;

	return Vec2(x, y);
}

void FightScene::updatePlayerMove( )
{
	if (m_FightControllerLayer->getisCanMove())
	{//判断要去的地方是否是障碍层
		float MoveAngle;
		MoveAngle = m_FightControllerLayer->getMoveRockerAngle();
		int TiledGid = m_WallLayer->getTileGIDAt(PositionToTiled
		(Vec2(m_Player->getPosition()
			+ MathUtils::getVectorialSpeed(MoveAngle, m_Player->getSpeed()/20))));
		if (TiledGid)
		{
			return;
		}
        m_Player->beganToMove(MoveAngle);
	}
	else
	{
        m_Player->stopMoving();
	} 
}


void FightScene::updatePlayerAttack(float nowTime)
{
	if (m_Player->isDead())
		return;

	float lastTime = m_Player->m_Character.m_Time;
	float delta = nowTime - lastTime;


	if (m_FightControllerLayer->m_AttackLayer->isAttackTime()&&delta>=m_Player->m_Character.m_IntervalTime)
	{
		m_Player->NormalAttack(m_FightControllerLayer->m_AttackLayer->getNormalRockerAngle(),nowTime);

		m_FightControllerLayer->m_AttackLayer->setAttackState(false);
	}
	else
	{
	}
}

void FightScene::startContactListen()
{
	m_ContactListener = EventListenerPhysicsContact::create();

	m_ContactListener->onContactBegin = CC_CALLBACK_1(FightScene::onContactBegin,this);
}

bool FightScene::onContactBegin(cocos2d::PhysicsContact& contact)
{

	Node* nodeA = contact.getShapeA()->getBody()->getNode();

	Node* nodeB = contact.getShapeB()->getBody()->getNode();

	/* 检测到碰撞时需要处理的情况 */
	if (nodeA && nodeB)
	{
		/* 两个武器碰撞 */
		if (nodeA->getName() == "Weapon" && nodeB->getName() == "Weapon")
		{
			if(nodeA != nullptr)
				nodeA->removeFromParentAndCleanup(true);
			if(nodeB != nullptr)
				nodeB->removeFromParentAndCleanup(true);
		}
		/* 角色被武器击中 */
		else if (nodeA->getName() == "Weapon" && nodeB->getName()=="PLayer")
		{
			/* 获取武器的使用者 */
			Weapon* weapon = (Weapon*)nodeA;
			Hero* Attacker = weapon->getOwner();

			/* 将武器从场景中移除 */
			if(weapon!=nullptr)
				weapon->removeFromParentAndCleanup(true);

			Hero* Injured = (Hero*)nodeB;

			Injured->BeAttacked(Attacker->m_Character.m_NormalAttackDamage);

			Attacker->AttackSomething();
		}
		/* 角色被武器击中 */
		else if (nodeB->getName()=="Weapon" && nodeA->getName()=="PLayer")
		{
			Weapon* weapon = (Weapon*)nodeB;
			Hero* Attacker = weapon->getOwner();

			/* 将武器从场景中移除 */
			if (weapon != nullptr)
				weapon->removeFromParentAndCleanup(true);

			Hero* Injured = (Hero*)nodeA;

			Injured->BeAttacked(Attacker->m_Character.m_NormalAttackDamage);

			Attacker->AttackSomething();
		}
	}
	return true;
}
