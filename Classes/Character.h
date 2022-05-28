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
	float m_Speed;

	/* ��ɫ�ĳ�ʼѪ�� */
	float m_BloodVolume;

	/* ��ɫ���չ��˺�ֵ */
	int m_NormalAttackDamage;

	/* ��ɫ�Ĵ����˺�ֵ */
	int m_AceDamage;

	/* ������ȴʱ�� */
	int m_Cooldown;

	//��д���ڲ�����
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
