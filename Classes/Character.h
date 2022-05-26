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
	int m_Speed;

	/* 角色的初始血量 */
	float m_BloodVolume;

	/* 角色的普攻伤害值 */
	int m_NormalAttackDamage;

	/* 角色的大招伤害值 */
	int m_AceDamage;

	/* 大招冷却时间 */
	int m_Cooldown;
};


#endif
