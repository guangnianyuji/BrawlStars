#include "FightScene.h"

FightScene* FightScene::create(std::vector<Character> CharacterVec)
{
	FightScene* pRet = new(std::nothrow)FightScene();

	Vec2 VisibleSize = Director::getInstance()->getVisibleSize();

	pRet->m_TiledMap = TMXTiledMap::create("map.tmx");

	pRet->m_Player = Player::create(CharacterVec[0]);

	for (int i = 1,AIi=0; i < 10; i++)
	{
		if (CharacterVec[i] == Nothing())
		{
			continue;
		}
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

	//�����ͼ
	addChild(m_TiledMap,-1);

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
				auto boxPhysicsBody = PhysicsBody::createBox(WallTiled->getContentSize());//����PhysicsBody���
				boxPhysicsBody->setDynamic(false);
				WallTiled->setPhysicsBody(boxPhysicsBody);//����Ƭ�����PhysicsBody���
			}
		}
	}
	
	//������ҳ�ʼλ��
	m_Player->setOriginalPositionInMap(m_TiledMap,"PlayerBirthPlace");
	//����Ҽ��뵽��ͼ��
	m_TiledMap->addChild(m_Player,4);	


	for (std::vector<AI*>::iterator it= m_AIVec.begin(); it!= m_AIVec.end(); it++)
	{
		(*it)->setOriginalPositionInMap(m_TiledMap, (*it)->getName()+"BirthPlace");
		m_TiledMap->addChild((*it), 4);
	}
		
	//�ڳ����м���ң��
	m_FightControllerLayer->startMoveRocker(true);

	//����������ײ����
	startContactListen();
	addChild(m_FightControllerLayer,2);

	//Ϊ��ҽڵ��������֣�����֮�����ײ���
	m_Player->setName("Player");

	scheduleUpdate();
	
	return true;
}

void FightScene::update(float delta)
{
	updatePlayerMove();
	updateViewPointByPlayer();
	//updatePlayerAttack();
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
	if (m_FightControllerLayer->getisCanMove())
	{//�ж�Ҫȥ�ĵط��Ƿ����ϰ���
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

/*
void FightScene::updatePlayerAttack()
{
	if (m_AttackLayer->isAttacking())
	{
		m_Player->NormalAttack(m_FightControllerLayer->getMoveRockerAngle());
	}
	else
	{
		m_Player->stopNormalAttack();
	}
}
*/
void FightScene::startContactListen()
{
	m_ContactListener = EventListenerPhysicsContact::create();

	m_ContactListener->onContactBegin = CC_CALLBACK_1(FightScene::OnContactBegin,this);
}

bool FightScene::OnContactBegin(cocos2d::PhysicsContact& contact)
{

	Node* nodeA = contact.getShapeA()->getBody()->getNode();

	Node* nodeB = contact.getShapeB()->getBody()->getNode();

	/* ��⵽��ײʱ��Ҫ�������� */
	if (nodeA && nodeB)
	{
		/* ����������ײ */
		if (nodeA->getName() == "Weapon" && nodeB->getName() == "Weapon")
		{
			if(nodeA != nullptr)
				nodeA->removeFromParentAndCleanup(true);
			if(nodeB != nullptr)
				nodeB->removeFromParentAndCleanup(true);
		}
		/* ��ɫ���������� */
		else if (nodeA->getName() == "Weapon" && nodeB->getName()=="Player")
		{
			/* ��ȡ������ʹ���� */
			Hero* Attacker = (Hero*)nodeA->getParent();

			/* �������ӳ������Ƴ� */
			if(nodeA!=nullptr)
				nodeA->removeFromParentAndCleanup(true);

			Hero* Injured = (Hero*)nodeB;

			Injured->BeAttacked(Attacker->m_Character.m_NormalAttackDamage);

			Attacker->AttackSomething();
		}
		/* ��ɫ���������� */
		else if (nodeB->getName()=="Weapon" && nodeA->getName()=="Player")
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


Vec2 FightScene::PositionToTiled(const Vec2& position)
{
	int x = position.x / m_TiledMap->getTileSize().width;

	int y = ((m_TiledMap->getMapSize().height * m_TiledMap->getTileSize().height) - position.y) /
		m_TiledMap->getTileSize().height;

	return Vec2(x, y);
}