#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"
#include "Entity.h"
#include "MathUtils.h"
#include "Character.h"
#include "ProgressView.h"
#include "Weapon.h"
#include "TimeCounter.h"

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
	void NormalAttack(const float Angle,float nowTime);

	//停止普通攻击
	void stopNormalAttack();

	//使用绝招
	void Ace(const float Angle);

	//停止绝招
	void stopAce();

	//打击到了某些东西
	virtual void AttackSomething() override;

	//被攻击到了
	virtual void BeAttacked(const float& Damage) override;

	//死亡
	virtual void Death() override;

	//判断英雄是否还活着
	inline bool isDead() { return m_isDead; }

	//判断现在是否可以使用绝招了
	inline bool canAceNow() { return m_Character.m_RealCount <= 0; }

	inline bool damageImmunity() { return m_damageImmunity; }

	//英雄的角色
	Character m_Character;

	TimeCounter* m_TimeCounter;

	//得到速度的接口
	float getSpeed();

private:

	//英雄的技能
	Sprite* m_Skill;

	//英雄的速度
	float m_Speed;

	//英雄是否正在移动
	bool m_isMoving;

	//英雄是否已经死亡
	bool m_isDead = false;

	//英雄是否免疫伤害
	bool m_damageImmunity = false;

	//英雄大致移动方向缩写(方便找动画文件)
	std::string m_Direction;


};

#endif
