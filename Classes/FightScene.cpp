#include "FightScene.h"

FightScene* FightScene::create(std::vector<Character> CharacterVec)
{
	FightScene* pRet = new(std::nothrow)FightScene();

	Vec2 VisibleSize = Director::getInstance()->getVisibleSize();

	pRet->m_TiledMap = TMXTiledMap::create("map.tmx");

	pRet->m_Player = Player::create(CharacterVec[0]);


	//初始化AI数组
	for (int i = 1,AIi=0; i < 10; i++)
	{
		if (CharacterVec[i] == Nothing())
		{
			//如果角色为Nothing,跳过
			continue;
		}
		//根据角色创建AI,放入AI数组，注意,m_AIVec[0]的编号为AI1
		pRet->m_AIVec.push_back(AI::create(CharacterVec[i]));
		pRet->m_AIVec[AIi]->setName("AI" + Value(i).asString());
		AIi++;
	}

	pRet->m_FightControllerLayer = FightControllerLayer::create();

	//pRet->m_AttackLayer = AttackLayer::create(Vec2(VisibleSize.x / 6 * 4.5, VisibleSize.y / 6),
	//Vec2(VisibleSize.x/8*7,VisibleSize.y/2));


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

	for (int i = 0; i < TiledNumber.width; i++)
	{
		for (int j = 0; j < TiledNumber.height; j++)// 这个循环遍历一遍所有瓦片
		{
			Sprite* WallTiled = m_WallLayer->tileAt(ccp(i, j));//获取wall层里的瓦片，瓦片是精灵，可以放在这个数组中
			if (WallTiled)//并不是所有位置都有瓦片，如果没有瓦片就是空
			{
				auto boxPhysicsBody = PhysicsBody::createBox(WallTiled->getContentSize());//设置PhysicsBody组件
				boxPhysicsBody->setDynamic(false);
				WallTiled->setPhysicsBody(boxPhysicsBody);//给瓦片添加上PhysicsBody组件
			}
		}
	}


	//设置玩家初始位置
	m_Player->setOriginalPositionInMap(m_TiledMap,"PlayerBirthPlace");
	//将玩家加入到地图中

	m_TiledMap->addChild(m_Player,4);	


	for (std::vector<AI*>::iterator it= m_AIVec.begin(); it!= m_AIVec.end(); it++)
	{
		(*it)->setOriginalPositionInMap(m_TiledMap, (*it)->getName()+"BirthPlace");
		m_TiledMap->addChild((*it), 4);
	}

	//在场景中加入遥杆
	m_FightControllerLayer = FightControllerLayer::create();
	
	m_FightControllerLayer->startAllRockers(true);

	//开启场景碰撞监听
	startContactListen();
	addChild(m_FightControllerLayer,2);

	//为玩家节点设置名字，方便之后的碰撞检测

	m_Player->setName("Player");

	//毒圈计时器开始计时
	m_ToxicFogTimeCounter = TimeCounter::create();
	addChild(m_ToxicFogTimeCounter);
	m_ToxicFogTimeCounter->startCounting();
	m_ToxicFogLevel = -1;//初始化，无意义
	for (int i = 0; i < m_TiledMap->getMapSize().width; i++)
	{
		for (int j = 0; j < m_TiledMap->getMapSize().width; j++)
		{
			m_ToxicFogMap[Vec2(i, j)] = false;
		}
	 }


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
	updateToxicFog();
	updateToxicFogDamage();
	//updatePlayerAttack();
	updatePlayerAttack(m_TimeCounter->getTime());
}

void FightScene::updateViewPointByPlayer()
{
	//地图方块数量
	Size TiledNumber = m_TiledMap->getMapSize();

	//地图单个格子大小
	Size TiledSize = m_TiledMap->getTileSize();

	//地图大小
	Size TiledMapSize = Size(TiledNumber.width * TiledSize.width,
		TiledNumber.height * TiledSize.height);

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
	if (m_FightControllerLayer->getMoveRockerIsMoving())
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


void FightScene::updateToxicFog()
{
	m_TempToxicFogLevel = m_ToxicFogTimeCounter->getTime()/30;
	if (m_TempToxicFogLevel == m_ToxicFogLevel)
	{
		return;
	}
	m_ToxicFogLevel = m_TempToxicFogLevel;
	int i, j;
	//绘制左侧毒雾
	i = m_ToxicFogLevel;
	for ( j = m_ToxicFogLevel;j < m_TiledMap->getMapSize().height - m_ToxicFogLevel; j++)
	{
		m_ToxicFogSpriteVec.push_back(Sprite::create("fog.png"));
		m_ToxicFogSpriteVec.back()->setPosition(TiledToPosition(Vec2(i, j)));
		m_TiledMap->addChild(m_ToxicFogSpriteVec.back(),5);
		m_ToxicFogMap[Vec2(i, j)] = true;
	}
	//绘制上侧毒雾
	j = m_ToxicFogLevel;
	for (i = m_ToxicFogLevel + 1; i< m_TiledMap->getMapSize().width - m_ToxicFogLevel; i++)
	{
		m_ToxicFogSpriteVec.push_back(Sprite::create("fog.png"));
		m_ToxicFogSpriteVec.back()->setPosition(TiledToPosition(Vec2(i, j)));
		m_TiledMap->addChild(m_ToxicFogSpriteVec.back(), 5);
		m_ToxicFogMap[Vec2(i, j)] = true;
	}
	//绘制下侧毒雾
	j = m_TiledMap->getMapSize().height - m_ToxicFogLevel-1;
	for (i = m_ToxicFogLevel + 1; i< m_TiledMap->getMapSize().width - m_ToxicFogLevel; i++)
	{
		m_ToxicFogSpriteVec.push_back(Sprite::create("fog.png"));
		m_ToxicFogSpriteVec.back()->setPosition(TiledToPosition(Vec2(i, j)));
		m_TiledMap->addChild(m_ToxicFogSpriteVec.back(), 5);
		m_ToxicFogMap[Vec2(i, j)] = true;
	}
	//绘制右侧毒雾
	i = m_TiledMap->getMapSize().width- m_ToxicFogLevel - 1;
	for (j = m_ToxicFogLevel; j < m_TiledMap->getMapSize().height - m_ToxicFogLevel; j++)
	{
		m_ToxicFogSpriteVec.push_back(Sprite::create("fog.png"));
		m_ToxicFogSpriteVec.back()->setPosition(TiledToPosition(Vec2(i, j)));
		m_TiledMap->addChild(m_ToxicFogSpriteVec.back(), 5);
		m_ToxicFogMap[Vec2(i, j)] = true;
	}
	
};

void FightScene::updateToxicFogDamage()
{
	if(m_ToxicFogMap[PositionToTiled(m_Player->getPosition())])
	{
		//m_Player->BeAttcked(20);
	}
	for (auto oneAI : m_AIVec)
	{
		if (m_ToxicFogMap[PositionToTiled(oneAI->getPosition())])
		{
			//oneAI->BeAttcked(20);
		}
	}
}

void FightScene::updatePlayerAttack(float nowTime)
{
	if (m_Player->isDead())
		return;

	float lastTime = m_Player->m_Character.m_Time;
	float delta = nowTime - lastTime;


	if (m_FightControllerLayer->getNormalAttackState()&&delta>=m_Player->m_Character.m_IntervalTime)
	{
		m_Player->NormalAttack(m_FightControllerLayer->getNormalAttackRockerAngle(),nowTime);

		m_FightControllerLayer->setNormalAttackState(false);
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


Vec2 FightScene::PositionToTiled(const Vec2& position)
{
	int x = position.x / m_TiledMap->getTileSize().width;

	int y = ((m_TiledMap->getMapSize().height * m_TiledMap->getTileSize().height) - position.y) /
		m_TiledMap->getTileSize().height;

	return Vec2(x, y);
}

Vec2 FightScene::TiledToPosition(const Vec2& position)
{
	int x= position.x* m_TiledMap->getTileSize().width+ 0.5* m_TiledMap->getTileSize().width;
	
	int y = (m_TiledMap->getMapSize().height - position.y) * m_TiledMap->getTileSize().height - 0.5 * m_TiledMap->getTileSize().height;
	
	return Vec2(x, y);
}
