#include "FightScene.h"
#include "Fei.h"

FightScene* FightScene::create(Character character)
{
	FightScene* pRet = new(std::nothrow)FightScene();
	Vec2 VisibleSize = Director::getInstance()->getVisibleSize();
	pRet->m_TiledMap = TMXTiledMap::create("map.tmx");
	pRet->m_Player = Player::create(character);
	pRet->m_FightControllerLayer = FightControllerLayer::create(Vec2(VisibleSize.x / 4, VisibleSize.y / 3));
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
	if (!Scene::init())
	{
		return false;
	}
	Vec2 VisibleSize = Director::getInstance()->getVisibleSize();

	addChild(m_TiledMap,-1);
	
	m_Player->setOriginalPositionInMap(m_TiledMap,"PlayerBirthPlace");
	m_TiledMap->addChild(m_Player,4);
		
	
	m_FightControllerLayer->startRocker(true);
	addChild(m_FightControllerLayer,2);

	scheduleUpdate();
	
	return true;
}

void FightScene::update(float delta)
{
	updatePlayerMove();
	updateViewPointByPlayer();
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
	if (m_FightControllerLayer->getisCanMove())
	{
        m_Player->setAnimation(m_FightControllerLayer->getRockerAngle());
	}
	else
	{
        m_Player->stopAnimation();
	} 
}