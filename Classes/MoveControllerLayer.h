#ifndef __MOVECONTROLLERLAYER_H__
#define __MOVECONTROLLERLAYER_H__

#include "cocos2d.h"
#include "Math.h"
using namespace cocos2d;

class MoveControllerLayer :public Layer
{
public:
	//创建控制层
	static MoveControllerLayer* create(Vec2 position);

	//启动摇杆（启动摇杆，监听键盘事件）
	void startRocker(bool isStop);

	//停止摇杆（隐藏摇杆，取消监听事件）
	void stopRocker();

	//得到是否能操控摇杆
	bool getisCanMove();

	//得到方向角
	float getRockerAngle();

private:
	//是否可操作摇杆
	bool m_isCanMove;

	//监听者
	EventListenerTouchOneByOne* m_TouchListener;
	EventListenerKeyboard* m_KeyboardListener;

	//初始化
	bool init()override;

	//摇杆节点
	Sprite* m_RockerBackgroundSprite;

	//摇杆背景节点
	Sprite* m_RockerSprite;

	//摇杆背景的坐标
	Vec2 m_RockerBackgroundPosition;

	//摇杆背景的半径
	float m_RockerBackgroundRadius;

	//摇杆的坐标
	Vec2 m_RockerPosition;

	//摇杆得到的方向角
	float m_RockerAngle;

	void update(float delta);

	//更新摇杆所指角度
	void updateRad( );
};

#endif//__MOVECONTROLLERLAYER_H__