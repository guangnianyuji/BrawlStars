#ifndef __FIGHTCONTROLLERLAYER_H__
#define __FIGHTCONTROLLERLAYER_H__

#include "cocos2d.h"
#include "Math.h"
#include "Character.h"
#include "Util/TimeCounter.h"

using namespace cocos2d;

class FightControllerLayer :public Layer
{

public:
	//创建控制层
	static FightControllerLayer* create(Character PlayerCharacter);

	//启动移动摇杆（启动摇杆，监听键盘事件）
	void startAllRockers();

	//停止移动摇杆（隐藏摇杆，取消监听事件）
	void stopAllRockers();


	//得到移动摇杆是否在移动
	bool getMoveRockerIsMoving() const { return m_keyboardMoveRockerIsMoving||m_touchMoveRockerIsMoving; }

	//得到移动摇杆移动的方向角
	float getMoveRockerAngle() const { return m_MoveRockerAngle; }

	//得到普通攻击摇杆是否在移动
	bool getNormalAttackRockerIsMoving() const{ return m_NormalAttackRockerIsMoving; }

	//得到普通攻击摇杆移动的方向角
	float getNormalAttackRockerAngle() const{ return m_NormalAttackRockerAngle; }

	//得到大招攻击摇杆是否在移动
	bool getACERockerIsMoving() const { return m_ACERockerIsMoving; }

	//得到大招攻击摇杆移动的方向角
	float getACERockerAngle() const { return m_ACERockerAngle; }

	//得到普通攻击状态
	bool getNormalAttackState() const { return m_NormalAttackState; }

	//设置普通攻击状态
	void setNormalAttackState(bool state) {  m_NormalAttackState=state; }

	//设置大招状态
	void setACEState(bool state) { m_ACEState = state; }

	//得到大招攻击状态
	bool getACEState() const { return m_ACEState; }

	//设置大招摇杆状态
	void setACERockerState(bool state);

	//得到大招摇杆状态
	bool getACERockerState() { return m_ACERockerSprite->isVisible(); }

	//记录普攻次数 
	void addCount() { m_Count++; }

	


private:

	EventListenerTouchAllAtOnce* m_TouchListener;

	EventListenerKeyboard* m_KeyboardListener;

	//初始化
	virtual bool init() override;	
	
	/* 加入移动和攻击摇杆 */
	void initMoveandAttackRocker();


	void initEventListener();

	//移动摇杆

	//移动摇杆节点
	Sprite* m_MoveRockerBackgroundSprite;

	//移动摇杆背景节点
	Sprite* m_MoveRockerSprite;

	//移动摇杆背景的坐标
	Vec2 m_MoveRockerBackgroundPosition;

	//移动摇杆背景的半径
	float m_MoveRockerBackgroundRadius;

	//移动摇杆的坐标
	Vec2 m_MoveRockerPosition;

	//移动摇杆得到的方向角
	float m_MoveRockerAngle;

    //键盘控制移动摇杆是否移动
	bool m_keyboardMoveRockerIsMoving;

	//触摸控制移动摇杆是否移动
	bool m_touchMoveRockerIsMoving;

	//普通攻击摇杆
	
	//普通攻击摇杆节点
	Sprite* m_NormalAttackRockerBackgroundSprite;

	//普通攻击摇杆背景节点
	Sprite* m_NormalAttackRockerSprite;

	//普通攻击摇杆背景的坐标
	Vec2 m_NormalAttackRockerBackgroundPosition;

	//普通攻击摇杆背景的半径
	float m_NormalAttackRockerBackgroundRadius;

	//普通攻击摇杆的坐标
	Vec2 m_NormalAttackRockerPosition;

	//普通攻击摇杆得到的方向角
	float m_NormalAttackRockerAngle;

	//普攻摇杆是否移动
	bool m_NormalAttackRockerIsMoving;

	//是否开始攻击
	bool m_NormalAttackState;

	//大招攻击摇杆

	//大招攻击摇杆节点
	Sprite* m_ACERockerBackgroundSprite;

	//大招攻击摇杆背景节点
	Sprite* m_ACERockerSprite;

	//大招攻击摇杆背景的坐标
	Vec2 m_ACERockerBackgroundPosition;

	//大招攻击摇杆背景的半径
	float m_ACERockerBackgroundRadius;

	//大招攻击摇杆的坐标
	Vec2 m_ACERockerPosition;

	//大招攻击摇杆得到的方向角
	float m_ACERockerAngle;
	
   //大招摇杆是否移动
	bool m_ACERockerIsMoving;

	//是否开始大招攻击
	bool m_ACEState;

	void update(float delta);

	//更新移动摇杆所指角度
	void updateMoveRad( );

	//更新大招按键的状态
	void updateACERockerState();

	//记录上一次普攻的时间
	float m_LastNormalAttackTime;

	//记录大招开始时间
	float m_StartACETime;

	//记录上一次大招的时间
	float m_LastACETime;

	//记录普攻次数，积攒大招
	int m_Count;

	TimeCounter* m_TimeCounter;

	Character m_Character;

};

#endif//__FIGHTCONTROLLERLAYER_H__