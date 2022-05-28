#ifndef  __FIGHTSCENE_H__
#define  __FIGHTSCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "BSScene\BaseScene.h"
#include "FightControllerLayer.h"
#include "AttackLayer.h"
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

	//播放技能动画函数
	void updatePlayerAttack();

	//在场景中开启碰撞监听
	void startContactListen();

	//监听到两物体开始碰撞的回调函数
	bool OnContactBegin(cocos2d::PhysicsContact& contact);


	TMXTiledMap* m_TiledMap;

	FightControllerLayer* m_FightControllerLayer;

	//AttackLayer* m_AttackLayer;

	Player* m_Player;

	EventListenerPhysicsContact* m_ContactListener;


};

#endif // ! __FIGHTSCENE_H__

