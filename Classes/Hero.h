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
	void beganToMove(const float& Angle,const float Speed,Point EndPosition);

	//停止动画播放，角色静止
	void stopMoving();

	//普通攻击
	void normalAttack(const float Angle);

	//停止普通攻击
	void stopNormalAttack();

	//使用绝招
	void ACE(const float Angle);

	//停止绝招
	void stopACE();

	//打击到了某些东西
	virtual void attackSomething();

	//被攻击到了
	virtual void beAttacked(const float& Damage) override;

	//死亡
	virtual void Death() override;

	bool isDead() const {return m_isDead;}

	//英雄是否处于免疫状态
	bool damageImmunity() const {return m_damageImmunity;}

	//英雄的角色
	Character m_Character;

	//得到速度的接口
	float getSpeed() const {return m_Speed;}

	//为击毁宝箱增加速度
	void addSpeed(float offerSpeed) { m_Speed += offerSpeed; }

	//得到普攻攻击力接口
	float getNormalAttackDamage() const{ return m_NormalAttackDamage;} 

	//为击毁宝箱提高普攻
	void addNormalAttackDamage(float offerAttackDamage){ m_NormalAttackDamage+= offerAttackDamage; }
private:


	//英雄的速度
	float m_Speed;

	//英雄是否正在移动
	bool m_isMoving;

	//英雄普攻伤害
	float m_NormalAttackDamage;

	//英雄大招伤害
	float m_AceDamage;

	//英雄是否已经死亡
	bool m_isDead = false;

	//英雄是否免疫伤害
	bool m_damageImmunity = false;

	//英雄大致移动方向缩写(方便找动画文件)
	std::string m_Direction;


};


#endif
