#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"
#include "Entity.h"
#include "MathUtils.h"
#include "Character.h"
#include "ProgressView.h"

using namespace cocos2d;

class Hero :public Entity
{

public:
	bool init() override;


	//动画播放，角色开始行走
	void beganToMove(const float& Angle);

	//停止动画播放，角色静止
	void stopMoving();

	//普通攻击
	void NormalAttack(const float& Angle);

	//停止普通攻击
	void stopNormalAttack();

	//打击到了某些东西
	virtual void AttackSomething() override;

	//被攻击到了
	virtual void BeAttacked(const float& Damage) override;

	//死亡
	virtual void Death() override;

	//英雄的角色
	Character m_Character;

private:
	//英雄的身体
	Sprite* m_Body;

	//英雄的技能
	Sprite* m_Skill;

	//英雄是否正在移动
	bool m_isMoving;

	//英雄大致移动方向缩写(方便找动画文件)
	std::string m_Direction;


};

#endif
