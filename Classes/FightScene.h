#ifndef  __FIGHTSCENE_H__
#define  __FIGHTSCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "AI.h"
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

    //更新毒雾
	void updateToxicFog();

	//更新毒雾伤害
	void updateToxicFogDamage();

	//播放技能动画函数
	//void updatePlayerAttack();

	//更新玩家的技能发射
	void updatePlayerAttack(float nowTime);

	//在场景中开启碰撞监听
	void startContactListen();

	//监听到两物体开始碰撞的回调函数
	bool onContactBegin(cocos2d::PhysicsContact& contact);


	TMXTiledMap* m_TiledMap;
	TMXLayer* m_WallLayer;

	std::map < Vec2, bool > m_ToxicFogMap;//记录某一瓦片位置是否有毒雾
	TimeCounter* m_ToxicFogTimeCounter;//增大毒雾范围的计时器
	int m_ToxicFogLevel;//毒圈的等级
	int m_TempToxicFogLevel;//毒圈的暂时等级
	std::vector<Sprite*> m_ToxicFogSpriteVec;

	FightControllerLayer* m_FightControllerLayer;

	Player* m_Player;
	std::vector<AI*> m_AIVec;

	EventListenerPhysicsContact* m_ContactListener;

	TimeCounter* m_TimeCounter;

	//工具类函数
	//让像素坐标转换为瓦片坐标
	Vec2 PositionToTiled(const Vec2& position);
	////让瓦片坐标转换为像素坐标
	Vec2 TiledToPosition(const Vec2& position);
};

#endif // ! __FIGHTSCENE_H__

