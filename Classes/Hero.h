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

	Sprite* m_Body;
	//英雄是否正在移动
	bool m_isMoving;

	void onEnter() override;
public:
	//动画播放
	void setAnimation(const float& Angle);
	//停止动画播放
	void stopAnimation();
};

#endif
