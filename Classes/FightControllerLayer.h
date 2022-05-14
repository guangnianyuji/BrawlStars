#ifndef _FIGHTCONTROLLERLAYER_H__
#define _FIGHTCONTROLLERLAYER_H__

#include "cocos2d.h"
#include "Math.h"
using namespace cocos2d;

class FightControllerLayer :public Layer
{
public:
	//创建控制层
	static FightControllerLayer* create();
	//启动摇杆（启动摇杆，监听键盘事件）
	void startRocker(bool isStop);
	//停止摇杆（隐藏摇杆，取消监听事件）
	void stopRocker();
	//判断控制杆方向，用来判断玩家上下左右移动
	int RocketDirection;
	

private:
	//是否可操作摇杆
	bool isCanMove;
	//监听者
	EventListenerTouchOneByOne* TouchListener;
	EventListenerKeyboard* KeyboardListener;
	//初始化
	bool init()override;
	//摇杆节点
	Sprite* RockerBackgroundSprite;
	//摇杆背景节点
	Sprite* RockerSprite;
	//摇杆背景的坐标
	Vec2 RockerBackgroundPosition;
	//摇杆背景的半径
	float RockerBackgroundRadius;
	//按键状态
	std::map <EventKeyboard::KeyCode, bool> KeyStateValueMap;

};

#endif//__FIGHTCONTROLLERLAYER_H__