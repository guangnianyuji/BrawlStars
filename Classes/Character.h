#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "Util/AnimationUtils.h"

USING_NS_CC;

class Character
{
public:
	/* 角色名 */
	std::string m_Name;

	/* 角色的初始速度 */
	float m_Speed = 0;

	/* 角色的初始血量 */
	float m_BloodVolume = 0;

	/* 角色的普攻伤害值 */
	float m_NormalAttackDamage = 0;

	/* 角色的大招伤害值 */
	float m_AceDamage = 0;

	/* 使用绝招所需要的普攻攒积次数 */
	int m_Count = 0;

	/* 角色的射程 */
	int m_Range = 0;

	/* 普通攻击的间隔时间 */
	float m_IntervalTime = 0;

	/* 绝招的可持续时间 */
	float m_Duration = 0;

	/* 绝招的间隔时间 */
	float m_ACEIntervalTime = 0;

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
