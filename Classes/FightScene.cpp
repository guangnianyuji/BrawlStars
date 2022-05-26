#include "FightScene.h"
#include "Fei.h"

FightScene* FightScene::create(Character character)
{
	FightScene* pRet = new(std::nothrow)FightScene();

	Vec2 VisibleSize = Director::getInstance()->getVisibleSize();

	pRet->m_TiledMap = TMXTiledMap::create("map.tmx");

	pRet->m_Player = Player::create(character);

	pRet->m_MoveControllerLayer = MoveControllerLayer::create(Vec2(VisibleSize.x / 4, VisibleSize.y / 3));

	pRet->m_AttackLayer = AttackLayer::create(Vec2(VisibleSize.x / 6 * 5, VisibleSize.y / 6),
	Vec2(VisibleSize.x/6*5,VisibleSize.y/3));

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
	
	//设置玩家初始位置
	m_Player->setOriginalPositionInMap(m_TiledMap,"PlayerBirthPlace");

	//将玩家加入到地图中
	m_TiledMap->addChild(m_Player,4);
		
	//在场景中加入遥杆
	m_MoveControllerLayer->startRocker(true);

	//在场景中加入攻击按键
	m_AttackLayer->setButtonEnable();

	//开启场景碰撞监听
	startContactListen();

	//为玩家节点设置名字，方便之后的碰撞检测
	m_Player->setName("Person");

	

	addChild(m_MoveControllerLayer,2);

	addChild(m_AttackLayer, 2);

	scheduleUpdate();
	
	return true;
}

void FightScene::update(float delta)
{
	updatePlayerMove();
	updateViewPointByPlayer();
	updatePlayerAttack();
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

void FightScene::updatePlayerMove( )
{
	if (m_MoveControllerLayer->getisCanMove())
	{
        m_Player->beganToMove(m_MoveControllerLayer->getRockerAngle());
	}
	else
	{
        m_Player->stopMoving();
	} 
}

void FightScene::updatePlayerAttack()
{
	if (m_AttackLayer->isAttacking())
	{
		m_Player->NormalAttack(m_MoveControllerLayer->getRockerAngle());
	}
	else
	{
		m_Player->stopNormalAttack();
	}
}

void FightScene::startContactListen()
{
	m_ContactListener = EventListenerPhysicsContact::create();

	m_ContactListener->onContactBegin = CC_CALLBACK_1(FightScene::OnContactBegin,this);
}

bool FightScene::OnContactBegin(cocos2d::PhysicsContact& contact)
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
		else if (nodeA->getName() == "Weapon" && nodeB->getName()=="Person")
		{
			/* 获取武器的使用者 */
			Hero* Attacker = (Hero*)nodeA->getParent();

			/* 将武器从场景中移除 */
			if(nodeA!=nullptr)
				nodeA->removeFromParentAndCleanup(true);

			Hero* Injured = (Hero*)nodeB;

			Injured->BeAttacked(Attacker->m_Character.m_NormalAttackDamage);

			Attacker->AttackSomething();
		}
		/* 角色被武器击中 */
		else if (nodeB->getName()=="Weapon" && nodeA->getName()=="Person")
		{
			Hero* Attacker = (Hero*)nodeB->getParent();

			if (nodeB != nullptr)
				nodeB->removeFromParentAndCleanup(true);

			Hero* Injured = (Hero*)nodeA;

			Injured->BeAttacked(Attacker->m_Character.m_NormalAttackDamage);

			Attacker->AttackSomething();

		}
	}
	return false;
}
