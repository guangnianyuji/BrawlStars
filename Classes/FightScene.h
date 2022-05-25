#ifndef  __FIGHTSCENE_H__
#define  __FIGHTSCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "BSScene\BaseScene.h"
#include "FightControllerLayer.h"
#include "AttackLayer.h"

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


	TMXTiledMap* m_TiledMap;

	FightControllerLayer* m_FightControllerLayer;

	AttackLayer* m_AttackLayer;

	Player* m_Player;


};

#endif // ! __FIGHTSCENE_H__

