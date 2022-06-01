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


	//�������ţ���ɫ��ʼ����
	void beganToMove(const float& Angle);

	//ֹͣ�������ţ���ɫ��ֹ
	void stopMoving();

	//��ͨ����
	void NormalAttack(const float Angle,float nowTime);

	//ֹͣ��ͨ����
	void stopNormalAttack();

	//ʹ�þ���
	void Ace(const float Angle);

	//ֹͣ����
	void stopAce();

	//�������ĳЩ����
	virtual void AttackSomething() override;

	//����������
	virtual void BeAttacked(const float& Damage) override;

	//����
	virtual void Death() override;

	bool isDead() const;

	//�ж������Ƿ����ʹ�þ�����
	bool canAceNow() const;

	//Ӣ���Ƿ�������״̬
	bool damageImmunity() const;

	//Ӣ�۵Ľ�ɫ
	Character m_Character;

	TimeCounter* m_TimeCounter;

	//�õ��ٶȵĽӿ�
	float getSpeed() const;

private:

	//Ӣ�۵ļ���
	Sprite* m_Skill;

	//Ӣ�۵��ٶ�
	float m_Speed;

	//Ӣ���Ƿ������ƶ�
	bool m_isMoving;

	//Ӣ���Ƿ��Ѿ�����
	bool m_isDead = false;

	//Ӣ���Ƿ������˺�
	bool m_damageImmunity = false;

	//Ӣ�۴����ƶ�������д(�����Ҷ����ļ�)
	std::string m_Direction;


};

inline bool Hero::isDead() const
{
	return m_isDead;
}

inline bool Hero::canAceNow() const
{
	return m_Character.m_RealCount <= 0;
}

inline bool Hero::damageImmunity() const
{
	return m_damageImmunity;
}

inline float Hero::getSpeed() const
{
	return m_Speed;
}

#endif
