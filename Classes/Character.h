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
	float m_Speed = 0;

	/* ��ɫ�ĳ�ʼѪ�� */
	float m_BloodVolume = 0;

	/* ��ɫ���չ��˺�ֵ */
	int m_NormalAttackDamage = 0;

	/* ��ɫ�Ĵ����˺�ֵ */
	int m_AceDamage = 0;

	/* ʹ�þ�������Ҫ���չ��ܻ����� */
	int m_Count = 0;

	/* �������ʹ�þ��л���Ҫ��������ͨ�������� */
	int m_RealCount = 0;

	/* ��ɫ����� */
	int m_Range = 0;

	/* ��ͨ�����ļ��ʱ�� */
	float m_IntervalTime = 0;

	/* ��һ�η�����ͨ������ʱ�� */
	float m_Time = 0;

	/* ���еĿɳ���ʱ�� */
	float m_Dutration = 0;

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
