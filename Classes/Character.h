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
	int m_Blood_Volume;

	/* 大招冷却时间 */
	int m_Cooldown;
};


#endif
