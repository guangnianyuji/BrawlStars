#include "FightScene.h"

FightScene* FightScene::create(std::vector<Character> CharacterVec,std::string& map)
{
	FightScene* pRet = new(std::nothrow)FightScene();

	Vec2 VisibleSize = Director::getInstance()->getVisibleSize();

	pRet->m_TiledMap = TMXTiledMap::create(map);

	pRet->m_Player = Player::create(CharacterVec[0]);

	//��ʼ��AI����
	for (int i = 1, AIi = 0; i < 10; i++)
	{
		if (CharacterVec[i] == Nothing())
		{
			//�����ɫΪNothing,����
			continue;
		}
		//���ݽ�ɫ����AI,����AI���飬ע��,m_AIVec[0]�ı��ΪAI1
		pRet->m_AIVec.push_back(AI::create(CharacterVec[i]));
		pRet->m_AIVec[AIi]->setName("AI" + Value(i).asString());
		AIi++;
	}


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

    m_TempSurvivorNumber=-1;//�����ʼ��������
	m_SurvivorLabel = Label::create();
	addChild(m_SurvivorLabel, 2);

	PathFinding::getInstance()->getMap(m_TiledMap);

	//�����ͼ
	addChild(m_TiledMap,-1);
	//������ҳ�ʼλ��
	m_Player->setOriginalPositionInMap(m_TiledMap,"PlayerBirthPlace");

	//����Ҽ��뵽��ͼ��
	m_Player->setArea(PathFinding::getInstance()->findArea(m_Player->getPosition()));

	m_TiledMap->addChild(m_Player,4);	

	getWall();

	addAI();

	addBox();

	initPauseButton();



	//�ڳ����м���ң��
	m_FightControllerLayer = FightControllerLayer::create(m_Player->m_Character);
	
	m_FightControllerLayer->startAllRockers();

	//����������ײ����
	startContactListen();
	addChild(m_FightControllerLayer,2);

	//Ϊ��ҽڵ��������֣�����֮�����ײ���
	m_Player->setName("Player");

	startToxic();

	this->schedule(schedule_selector(FightScene::updatePositionInformation), 0.5f);

	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	schedule(schedule_selector(FightScene::updatePositionInformation), 0.5f);
	scheduleUpdate();
	
	return true;
}

void FightScene::initPauseButton()
{
	Vec2 VisibleSize = Director::getInstance()->getVisibleSize();

	auto PauseButton = Button::create("ui/Pause.png");
	PauseButton->setScale(0.6);
	PauseButton->setPosition(Vec2(VisibleSize.x - PauseButton->getContentSize().width / 2,
		PauseButton->getContentSize().height / 2));
	addChild(PauseButton, 1);
	PauseButton->addTouchEventListener([&](Ref* psender, Widget::TouchEventType type)
		{
			Vec2 size = Director::getInstance()->getVisibleSize();
			auto renderTexture = RenderTexture::create(size.x, size.y);
			//������ǰ��������ӽڵ���Ϣ������renderTexture�С�
			//�������ƽ�ͼ��
			if (renderTexture != nullptr)
			{
				renderTexture->begin();
				if (this != nullptr)
				{
					this->visit();
				}

				renderTexture->end();
			}

			auto PauseScene = PauseScene::create(renderTexture);
			//����Ϸ������ͣ��ѹ�볡����ջ�����л���Pause����
			if (PauseScene != nullptr)
			{
				Director::getInstance()->pushScene(PauseScene);
			}

		});
}

void FightScene::updateSurvivorLabel()
{
	if (m_TempSurvivorNumber == m_SurvivorNumber)
	{
		return;
	}
	m_TempSurvivorNumber = m_SurvivorNumber;

	removeChild(m_SurvivorLabel);

	Vec2 VisibleSize = Director::getInstance()->getVisibleSize();

	auto m_SurvivorLabel = Label::createWithTTF("SURVIVOR NUMBER:"+Value(m_SurvivorNumber).asString(),
		"fonts/Marker Felt.ttf", 30);
	m_SurvivorLabel->setPosition(Vec2(VisibleSize.x * 7 / 8, VisibleSize.y * 9/ 10));
	addChild(m_SurvivorLabel,2);
}

void FightScene::startToxic()
{
	//��Ȧ��ʱ����ʼ��ʱ
	m_ToxicFogTimeCounter = TimeCounter::create();
	addChild(m_ToxicFogTimeCounter);
	m_ToxicFogTimeCounter->startCounting();
	m_ToxicFogLevel = -1;//��ʼ����������
	for (int i = 0; i < m_TiledMap->getMapSize().width; i++)
	{
		for (int j = 0; j < m_TiledMap->getMapSize().width; j++)
		{
			m_ToxicFogMap[Vec2(i, j)] = false;
		}
	}


}

void FightScene::getWall()
{
	//��ȡ�ϰ���
	m_WallLayer = m_TiledMap->layerNamed("wall");//��ȡ��Ҫ���PhysicsBody����Ƭ���ڵ�ͼ��
	Size TiledNumber = m_TiledMap->getMapSize();

	for (int i = 0; i < TiledNumber.width; i++)
	{
		for (int j = 0; j < TiledNumber.height; j++)// ���ѭ������һ��������Ƭ
		{
			Sprite* WallTiled = m_WallLayer->tileAt(ccp(i, j));//��ȡwall�������Ƭ����Ƭ�Ǿ��飬���Է������������
			if (WallTiled)//����������λ�ö�����Ƭ�����û����Ƭ���ǿ�
			{
				PathFinding::getInstance()->updateUnsafePlace(Point(i, j));

				auto boxPhysicsBody = PhysicsBody::createBox(WallTiled->getContentSize());//����PhysicsBody���
				boxPhysicsBody->setDynamic(false);
				boxPhysicsBody->setCategoryBitmask(0x0001);
				boxPhysicsBody->setCollisionBitmask(0x0001);
				boxPhysicsBody->setContactTestBitmask(0x0001);
				WallTiled->setPhysicsBody(boxPhysicsBody);//����Ƭ�����PhysicsBody���
				WallTiled->setName("Wall");
				m_WallTield.push_back(WallTiled);
			}
		}
	}
}

void FightScene::addAI()
{
	int count = 1;

	for (std::vector<AI*>::iterator it = m_AIVec.begin(); it != m_AIVec.end(); it++)
	{
		(*it)->setOriginalPositionInMap(m_TiledMap, (*it)->getName() + "BirthPlace");
		(*it)->setName("AI");
		m_TiledMap->addChild((*it), 4);
		//��AI���뵽��ͼ��
		(*it)->setArea(PathFinding::getInstance()->findArea((*it)->getPosition()));


		/* ��AI��FSM�����ţ����㶨�򷢲���Ϣ */
		(*it)->getFSM()->setMark(Value(count).asString());

		/* ������Ϣ */
		(*it)->getFSM()->addObservers();
		count++;
	}

	
}

void FightScene::addBox()
{
	for (int i = 0; i < 10; i++)
	{
		m_BoxVec.push_back(Box::create());
		Vec2 TiledPosition = RandomTiledforBox();
		m_canPutBox[TiledPosition] = false;
		if (m_BoxVec[i] == nullptr)
		{
			continue;
		}
		m_BoxVec[i]->setName("Box");
		m_BoxVec[i]->setPosition(MathUtils::TiledToPosition(TiledPosition, m_TiledMap));
		m_TiledMap->addChild(m_BoxVec[i], 4);
	}
}

void FightScene::update(float delta)
{
	updatePlayerMove();
	updateViewPointByPlayer();
	updateToxicFog();
	updateToxicFogDamage();
	updateBox();
	updatePlayerAttack();
	updatePlayerACE();
	updateSurvivor();
	updateSurvivorLabel();
}

void FightScene::updateSurvivor()
{
	m_SurvivorNumber = 1;
	for (auto &AI : m_AIVec)
	{
		if (!AI->isDead())
		{
			m_SurvivorNumber++;
		}
	}
	if (m_Player->isDead()||m_SurvivorNumber==1)
	{
		Director::getInstance()->pushScene(ScoreScene::create(m_SurvivorNumber));
	}
}

void FightScene::updateViewPointByPlayer()
{
	//��ͼ��������
	Size TiledNumber = m_TiledMap->getMapSize();

	//��ͼ�������Ӵ�С
	Size TiledSize = m_TiledMap->getTileSize();

	//��ͼ��С
	Size TiledMapSize = Size(TiledNumber.width * TiledSize.width,
		TiledNumber.height * TiledSize.height);

	//��Ļ��С
	Size VisibleSize = Director::getInstance()->getVisibleSize();

	//��ȡ��������
	Point PlayerPosition = m_Player->getPosition();

	//��ȡ����
	float x = std::max(PlayerPosition.x, VisibleSize.width/ 2);
	float y = std::max(PlayerPosition.y,VisibleSize.height / 2);

	//��� x,y����������Ͻǵļ���ֵ����ȡ����ֵ������
	x = std::min(x, TiledMapSize.width - VisibleSize.width / 2);
	y = std::min(y, TiledMapSize.height - VisibleSize.height/ 2);

	Point DestinationPosition = Point(x, y);

	Point CenterPosition = VisibleSize / 2;

	m_TiledMap->setPosition(CenterPosition - DestinationPosition);
}

void FightScene::updatePlayerMove( )
{
	if (m_FightControllerLayer->getMoveRockerIsMoving())
	{//�ж�Ҫȥ�ĵط��Ƿ����ϰ���
		float MoveAngle;
		MoveAngle = m_FightControllerLayer->getMoveRockerAngle();
		int TiledGid = m_WallLayer->getTileGIDAt(MathUtils::PositionToTiled
		(Vec2(m_Player->getPosition()
			+ MathUtils::getVectorialSpeed(MoveAngle, m_Player->getSpeed()/60)),
				m_TiledMap));
		if (TiledGid)
		{
			return;
		}
        m_Player->beganToMove(MoveAngle,m_Player->getSpeed(),Vec2(0,0));
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
	//������඾��
	i = m_ToxicFogLevel;
	for ( j = m_ToxicFogLevel;j < m_TiledMap->getMapSize().height - m_ToxicFogLevel; j++)
	{
		m_ToxicFogSpriteVec.push_back(Sprite::create("fog.png"));
		m_ToxicFogSpriteVec.back()->setPosition(MathUtils::TiledToPosition(Vec2(i, j),m_TiledMap));
		m_TiledMap->addChild(m_ToxicFogSpriteVec.back(),5);
		m_ToxicFogMap[Vec2(i, j)] = true;

		PathFinding::getInstance()->updateUnsafePlace(Vec2(i, j));
	}
	//�����ϲ඾��
	j = m_ToxicFogLevel;
	for (i = m_ToxicFogLevel + 1; i< m_TiledMap->getMapSize().width - m_ToxicFogLevel; i++)
	{
		m_ToxicFogSpriteVec.push_back(Sprite::create("fog.png"));
		m_ToxicFogSpriteVec.back()->setPosition(MathUtils::TiledToPosition(Vec2(i, j),m_TiledMap));
		m_TiledMap->addChild(m_ToxicFogSpriteVec.back(), 5);
		m_ToxicFogMap[Vec2(i, j)] = true;

		PathFinding::getInstance()->updateUnsafePlace(Vec2(i, j));
	}
	//�����²඾��
	j = m_TiledMap->getMapSize().height - m_ToxicFogLevel-1;
	for (i = m_ToxicFogLevel + 1; i< m_TiledMap->getMapSize().width - m_ToxicFogLevel; i++)
	{
		m_ToxicFogSpriteVec.push_back(Sprite::create("fog.png"));
		m_ToxicFogSpriteVec.back()->setPosition(MathUtils::TiledToPosition(Vec2(i, j),m_TiledMap));
		m_TiledMap->addChild(m_ToxicFogSpriteVec.back(), 5);
		m_ToxicFogMap[Vec2(i, j)] = true;

		PathFinding::getInstance()->updateUnsafePlace(Vec2(i, j));
	}
	//�����Ҳ඾��
	i = m_TiledMap->getMapSize().width- m_ToxicFogLevel - 1;
	for (j = m_ToxicFogLevel; j < m_TiledMap->getMapSize().height - m_ToxicFogLevel; j++)
	{
		m_ToxicFogSpriteVec.push_back(Sprite::create("fog.png"));
		m_ToxicFogSpriteVec.back()->setPosition(MathUtils::TiledToPosition(Vec2(i, j),m_TiledMap));
		m_TiledMap->addChild(m_ToxicFogSpriteVec.back(), 5);
		m_ToxicFogMap[Vec2(i, j)] = true;

		PathFinding::getInstance()->updateUnsafePlace(Vec2(i, j));
	}
	
};

void FightScene::updateToxicFogDamage()
{
	if(m_ToxicFogMap[MathUtils::PositionToTiled(m_Player->getPosition(),m_TiledMap)])
	{
		m_Player->beAttacked(5);
	}
	for (auto& oneAI : m_AIVec)
	{
		if (oneAI->getParent() != nullptr)
		{
			if (m_ToxicFogMap[MathUtils::PositionToTiled(oneAI->getPosition(),m_TiledMap)])
			{
				oneAI->beAttacked(5);

				NotifyUtil::getInstance()->postNotification("touching The Smog" + oneAI->getFSM()->getMark(), (Ref*)"aaa");
			}
		}
	}
}

void FightScene::updateBox()
{
	for (auto& oneBox : m_BoxVec)
	{
		if (oneBox == nullptr)
		{
			continue;
		}
		if (oneBox->isDead())
		{
			Vec2 TiledPosition = MathUtils::PositionToTiled(oneBox->getPosition(),m_TiledMap);
			oneBox->setPosition(MathUtils::TiledToPosition(RandomTiledforBox(),m_TiledMap));
			m_canPutBox[TiledPosition] = true;
			oneBox->setisDead(false);
		
			int nowArea = PathFinding::getInstance()->findArea(oneBox->getPosition());

			oneBox->setArea(nowArea);

		}
	}
}

void FightScene::updatePositionInformation(float delta)
{
	for (int ix = 0; ix <= m_AIVec.size() - 1; ix++)
	{
		Point position1 = m_Player->getPosition();
		Point position2 = m_AIVec[ix]->getPosition();

		if(position1.distance(position2)<=200)
			NotifyUtil::getInstance()->postNotification("new Hero" + m_AIVec[ix]->getFSM()->getMark(), (Hero*)m_Player);
		for (int jx = 0; jx <= ix; jx++)
		{
			if (ix != jx)
			{
				if (m_AIVec[ix]->isDead() || m_AIVec[jx]->isDead())
					continue;
				Point position1 = m_AIVec[ix]->getPosition();
				Point position2 = m_AIVec[jx]->getPosition();
				if (position1.distance(position2) <= 200)
				{
					NotifyUtil::getInstance()->postNotification("new Hero" + m_AIVec[ix]->getFSM()->getMark(),(Hero*)m_AIVec[jx]);

					NotifyUtil::getInstance()->postNotification("new Hero" + m_AIVec[jx]->getFSM()->getMark(), (Hero*)m_AIVec[ix]);
				}
			}
		}
	}

	for (int ix = 0; ix <= m_BoxVec.size() - 1; ix++)
	{
		for (int jx = 0; jx <= m_AIVec.size() - 1 ; jx++)
		{
			Point position1 = m_BoxVec[ix]->getPosition();
			Point position2 = m_AIVec[jx]->getPosition();

			if (position1.distance(position2) <= 200)
			{
				NotifyUtil::getInstance()->postNotification("new Box" + m_AIVec[jx]->getFSM()->getMark(), m_BoxVec[ix]);
			}
		}
	}
}

void FightScene::updatePlayerAttack()
{
	if (m_Player->isDead())
		return;

	if (m_FightControllerLayer->getNormalAttackState())
	{
		m_Player->normalAttack(m_FightControllerLayer->getNormalAttackRockerAngle());

		if(!m_FightControllerLayer->getACERockerState())
			m_FightControllerLayer->addCount();

		m_FightControllerLayer->setNormalAttackState(false);
	}
}

void FightScene::updatePlayerACE()
{
	if (m_Player->isDead())
		return;

	if (m_FightControllerLayer->getACEState())
	{
		m_Player->ACE(m_FightControllerLayer->getACERockerAngle());
		m_FightControllerLayer->setACEState(false);
	}
	
	if(!m_FightControllerLayer->getACERockerState())
	{
		if (m_Player->damageImmunity())
			m_Player->stopACE();

		if (m_Player->getSpeed() != m_Player->m_Character.m_Speed)
			m_Player->stopACE();
	}
}

	

void FightScene::startContactListen()
{
	m_ContactListener = EventListenerPhysicsContact::create();
	m_ContactListener->onContactBegin = CC_CALLBACK_1(FightScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_ContactListener, this);
}

bool FightScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
	Player* player = nullptr; 
	AI* ai = nullptr;
	Weapon* weapon1 = nullptr;
	Weapon* weapon2 = nullptr;
	Sprite* wall = nullptr;
	Box* box = nullptr;

	Node* nodeA = contact.getShapeA()->getBody()->getNode();
	Node* nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{

		if (nodeA->getName() == "Wall") wall = (Sprite*)nodeA;
		else if (nodeB->getName() == "Wall") wall = (Sprite*)nodeB;

		if (nodeA->getName() == "Player") player = (Player*)nodeA;
		else if (nodeB->getName() == "Player") player = (Player*)nodeB;

		if (nodeA->getName() == "Box") box = (Box*)nodeA;
		else if (nodeB->getName() == "Box") box = (Box*)nodeB;

		if (nodeA->getName() == "AI") ai = (AI*)nodeA;
		else if (nodeB->getName() == "AI")ai = (AI*)nodeB;
	
		if (nodeA->getName() == "Weapon") weapon1 = (Weapon*)nodeA;
		if (nodeB->getName() == "Weapon" && !weapon1) weapon1 = (Weapon*)nodeB;
		if (nodeB->getName() == "Weapon" && weapon1) weapon2 = (Weapon*)nodeB;


		if (weapon1 && weapon2)
		{
			if (weapon1->getOwner() != weapon2->getOwner())
			{
				if (weapon1)
					weapon1->removeFromParentAndCleanup(true);
				if (weapon2)
					weapon2->removeFromParentAndCleanup(true);
			}
		}
		if (weapon1 && wall)
		{
			if (weapon1)
				weapon1->removeFromParentAndCleanup(true);
		}
		if (ai && weapon1)
		{
			Hero* attacker = weapon1->getOwner();

			if (attacker != ai)
			{
				if (ai)
				{
					ai->beAttacked(weapon1->getDamage());

				NotifyUtil::getInstance()->postNotification("being Attacked" + ai->getFSM()->getMark(), attacker);
				}
				if (attacker)
				{
					attacker->attackSomething();
				}
				NotifyUtil::getInstance()->postNotification("being Attacked" + ai->getFSM()->getMark(), attacker);
			}

		}
		if (player && weapon1)
		{
			Hero* attacker = weapon1->getOwner();

			if (attacker != player)
			{
				if (player)
				{
					player->beAttacked(weapon1->getDamage());
				}
				if (attacker)
				{
					attacker->attackSomething();
				}
				NotifyUtil::getInstance()->postNotification("hit The Enemy" + ((AI*)attacker)->getFSM()->getMark(),player);
			}
		}
		if (box && weapon1)
		{
			Hero* attacker = weapon1->getOwner();

			box->beAttacked(weapon1->getDamage());

			attacker->attackSomething();


			if (box->isDead())
			{
				attacker->beAttacked(-box->getofferBlood());
				attacker->addNormalAttackDamage(box->getofferDamage());
			}
			weapon1->removeFromParentAndCleanup(true);
		}
	}
	return true;
}


Vec2 FightScene::RandomTiledforBox()
{
	int x, y;
	do
	{
		x = rand() % int(m_TiledMap->getMapSize().width);
		y = rand() % int(m_TiledMap->getMapSize().height);
		if (m_canPutBox.find(Vec2(x, y)) == m_canPutBox.end() || m_canPutBox[Vec2(x, y)])
		{
			if (!m_WallLayer->getTileGIDAt(Vec2(x, y)))
			{
				break;
			}
		}
	} while (1);

	return Vec2(x, y);
}
