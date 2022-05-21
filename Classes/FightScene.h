#ifndef  __FIGHTSCENE_H__
#define  __FIGHTSCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "TiledMapUtils.h"
#include "FightControllerLayer.h"

using namespace cocos2d;

class FightScene:public Scene
{
public:
	//创造场景
	static FightScene* create(Character character);

private:	
	//初始化场景
	bool init() override;
    //让地图随主角滚动
	void setViewPointByPlayer();

	//更新玩家行走状态
	void updatePlayerMove(float delta);

	TMXTiledMap* m_TiledMap;
	FightControllerLayer* m_FightControllerLayer;
	Player* m_Player;


};

#endif // ! __FIGHTSCENE_H__

