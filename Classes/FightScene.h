#ifndef  __FIGHTSCENE_H__
#define  __FIGHTSCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "BSScene\BaseScene.h"
#include "FightControllerLayer.h"
#include "AttackLayer.h"
#include "Character.h"
#include "TimeCounter.h"
#include  <typeinfo>

using namespace cocos2d;

class FightScene:public BaseScene
{
public:
	//创造场景
	static FightScene* create(Character character);

private:	
	//初始化场景
	bool init() override;

	void update(float delta);

    //让地图随主角滚动
	void updateViewPointByPlayer();

	//更新玩家行走状态
	void updatePlayerMove();

	//更新玩家的普攻技能发射
	void updatePlayerAttack(float nowTime);

	//更新玩家的绝招技能发射
	void updatePlayerAce();

	//在场景中开启碰撞监听
	void startContactListen();

	//监听到两物体开始碰撞的回调函数
	bool onContactBegin(cocos2d::PhysicsContact& contact);


	TMXTiledMap* m_TiledMap;
	TMXLayer* m_WallLayer;

	FightControllerLayer* m_FightControllerLayer;

	Player* m_Player;

	EventListenerPhysicsContact* m_ContactListener;

	TimeCounter* m_TimeCounter;

	//工具类函数
	//让像素坐标转换为瓦片坐标
	Vec2 PositionToTiled(const Vec2& position);
};

#endif // ! __FIGHTSCENE_H__

