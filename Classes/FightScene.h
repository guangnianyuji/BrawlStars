#ifndef  __FIGHTSCENE_H__
#define  __FIGHTSCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "AI.h"
#include "Box.h"
#include "FightControllerLayer.h"
#include "TimeCounter.h"
#include "PauseScene.h"
#include "MathUtils.h"
#include "NotifyUtil.h"
#include "PathFinding.h"
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

	void initPauseButton();

	void startToxic();

	void getWall();

	void addAI();

	//开始的时候将宝箱添加进场景
	void addBox();




	void update(float delta);

    //让地图随主角滚动
	void updateViewPointByPlayer();

	//更新玩家行走状态
	void updatePlayerMove();

    //更新毒雾
	void updateToxicFog();

	//更新毒雾伤害
	void updateToxicFogDamage();

	//更新玩家的技能发射
	void updatePlayerAttack();

	//更新玩家的绝招技能发射
	void updatePlayerACE();

	//在场景中开启碰撞监听
	void startContactListen();

	//更新宝箱
	void updateBox();

	//更新Hero以及Box的位置信息，并发布通知
	void updatePositionInformation(float delta);

	//监听到两物体开始碰撞的回调函数
	bool onContactBegin(cocos2d::PhysicsContact& contact);


	TMXTiledMap* m_TiledMap;
	TMXLayer* m_WallLayer;
	std::vector<Sprite*> m_WallTield;

	std::map < Vec2, bool > m_ToxicFogMap;//记录某一瓦片位置是否有毒雾
	TimeCounter* m_ToxicFogTimeCounter;//增大毒雾范围的计时器
	int m_ToxicFogLevel;//毒圈的等级
	int m_TempToxicFogLevel;//毒圈的暂时等级
	std::vector<Sprite*> m_ToxicFogSpriteVec;

	FightControllerLayer* m_FightControllerLayer;

	Player* m_Player;

	std::vector<AI*> m_AIVec;
	std::vector<Box*> m_BoxVec;
     std::map<Vec2, bool> m_canPutBox;

	EventListenerPhysicsContact* m_ContactListener;
	
	//为宝箱产生随机位置
	Vec2 RandomTiledforBox();
};

#endif // ! __FIGHTSCENE_H__

