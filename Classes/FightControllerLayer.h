#ifndef __FIGHTCONTROLLERLAYER_H__
#define __FIGHTCONTROLLERLAYER_H__

#include "cocos2d.h"
#include "Math.h"
#include "AttackLayer.h"
using namespace cocos2d;

class AttackLayer;

class FightControllerLayer :public Layer
{
	friend class AttackLayer;
public:
	//创建控制层
	static FightControllerLayer* create(Vec2 position,const std::string characterName);

	//启动移动摇杆（启动摇杆，监听键盘事件）
	void startMoveRocker(bool isStop);

	//停止移动摇杆（隐藏摇杆，取消监听事件）
	void stopMoveRocker();

	//得到是否能操控移动摇杆
	bool getisCanMove();

	//得到方向角
	float getMoveRockerAngle();

	AttackLayer* m_AttackLayer;

private:


	void initMoveRocker();

	void initEventListener();

	//是否可操作移动摇杆
	bool m_isCanMove;

	EventListenerTouchAllAtOnce* m_TouchListener;

	EventListenerKeyboard* m_KeyboardListener;

	//初始化
	virtual bool init() override;

	//摇杆节点
	Sprite* m_MoveRockerBackgroundSprite;

	//摇杆背景节点
	Sprite* m_MoveRockerSprite;

	//摇杆背景的坐标
	Vec2 m_MoveRockerBackgroundPosition;

	//摇杆背景的半径
	float m_MoveRockerBackgroundRadius;

	//摇杆的坐标
	Vec2 m_MoveRockerPosition;

	//摇杆得到的方向角
	float m_MoveRockerAngle;

	void update(float delta);

	//更新摇杆所指角度
	void updateRad( );

};

#endif//__FIGHTCONTROLLERLAYER_H__