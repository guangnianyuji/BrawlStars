#ifndef  __FIGHTSCENE_H__
#define  __FIGHTSCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "AI.h"
#include "BSScene\BaseScene.h"
#include "FightControllerLayer.h"
#include "AttackLayer.h"
#include "Character.h"
#include  <typeinfo>

using namespace cocos2d;

class FightScene:public BaseScene
{
public:
	//创造场景
	static FightScene* create(std::vector<Character>);

private:	
	//初始化场景
	bool init() override;

	//void onEnter() override;

	void update(float delta);

    //让地图随主角滚动
	void updateViewPointByPlayer();

	//更新玩家行走状态
	void updatePlayerMove();

	//播放技能动画函数
	//void updatePlayerAttack();

	//在场景中开启碰撞监听
	void startContactListen();

	//监听到两物体开始碰撞的回调函数
	bool OnContactBegin(cocos2d::PhysicsContact& contact);


	TMXTiledMap* m_TiledMap;
	TMXLayer* m_WallLayer;

	FightControllerLayer* m_FightControllerLayer;

	//AttackLayer* m_AttackLayer;

	Player* m_Player;
	std::vector<AI*> m_AIVec;

	EventListenerPhysicsContact* m_ContactListener;

	//工具类函数
	//让像素坐标转换为瓦片坐标
	Vec2 PositionToTiled(const Vec2& position);
};

#endif // ! __FIGHTSCENE_H__

