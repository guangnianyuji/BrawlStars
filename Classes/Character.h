#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "AnimationUtils.h"

USING_NS_CC;

class Character
{
public:
	/* ��ɫ�� */
	std::string m_Name;

	/* ��ɫ�ĳ�ʼ�ٶ� */
	int m_Speed;

	/* ��ɫ�ĳ�ʼѪ�� */
	int m_BloodVolume;

	/* ��ɫ���չ��˺�ֵ */
	int m_NormalAttackDamage;

	/* ��ɫ�Ĵ����˺�ֵ */
	int m_AceDamage;

	/* ������ȴʱ�� */
	int m_Cooldown;
};


#endif
