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

	//�����ͼ
	addChild(m_TiledMap,-1);
	
	//������ҳ�ʼλ��
	m_Player->setOriginalPositionInMap(m_TiledMap,"PlayerBirthPlace");

	//����Ҽ��뵽��ͼ��
	m_TiledMap->addChild(m_Player,4);
		
	//�ڳ����м���ң��
	m_MoveControllerLayer->startRocker(true);

	//�ڳ����м��빥������
	m_AttackLayer->setButtonEnable();

	//����������ײ����
	startContactListen();

	//Ϊ��ҽڵ��������֣�����֮�����ײ���
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
	//��ͼ��������
	Size TiledNumber = m_TiledMap->getMapSize();

	//��ͼ�������Ӵ�С
	Size TiledSize = m_TiledMap->getTileSize();

	//��ͼ��С
	Size TiledMapSize = Size(TiledNumber.width * TiledNumber.width,
		TiledNumber.height * TiledNumber.height);

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
		else if (nodeA->getName() == "Weapon" && nodeB->getName()=="Person")
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
