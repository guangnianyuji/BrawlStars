#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "AnimationUtils.h"

USING_NS_CC;

class Character
{
public:
	/* 角色名 */
	std::string m_Name;

	/* 角色的初始速度 */
	float m_Speed;

	/* 角色的初始血量 */
	float m_BloodVolume;

	/* 角色的普攻伤害值 */
	int m_NormalAttackDamage;

	/* 角色的大招伤害值 */
	int m_AceDamage;

	/* 大招冷却时间 */
	int m_Cooldown;

	/* 角色的射程 */
	int m_Range;

	/* 普通攻击的间隔时间 */
	float m_IntervalTime;

	/* 上一次发出普通攻击的时间 */
	float m_Time;

	//重写等于操作符
	bool operator==(Character& aCharacter);
};


class Fei :public Character
{
public:
	Fei();

};

class Yu :public Character
{
public:
	Yu();

};
class Jide :public Character
{
public:
	Jide();

};
class Lin :public Character
{
public:
	Lin();

};
class Nothing :public Character
{
public:
	Nothing();
};
#endif
