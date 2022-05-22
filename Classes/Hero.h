#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"
#include "Entity.h"
#include "MathUtils.h"
#include "Character.h"

using namespace cocos2d;

class Hero :public Entity
{
public:
	bool init() override;
protected:

	//英雄的角色
	Character m_Character;

	//英雄的身体
	Sprite* m_Body;

	//英雄是否正在移动
	bool m_isMoving;

	//英雄大致移动方向缩写(方便找动画文件)
	std::string m_Direction;
public:
	//动画播放
	void setAnimation(const float& Angle);
	//停止动画播放
	void stopAnimation();
};

#endif
