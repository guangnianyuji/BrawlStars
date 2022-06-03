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
	void beganToMove(const float& Angle,const float Speed);

	//ֹͣ�������ţ���ɫ��ֹ
	void stopMoving();

	//��ͨ����
	void normalAttack(const float Angle);

	//ֹͣ��ͨ����
	void stopNormalAttack();

	//ʹ�þ���
	void ACE(const float Angle);

	//ֹͣ����
	void stopACE();

	//�������ĳЩ����
	virtual void attackSomething();

	//����������
	virtual void beAttacked(const float& Damage) override;

	//����
	virtual void Death() override;

	bool isDead() const {return m_isDead;}

	//Ӣ���Ƿ�������״̬
	bool damageImmunity() const {return m_damageImmunity;}

	//Ӣ�۵Ľ�ɫ
	Character m_Character;

	//�õ��ٶȵĽӿ�
	float getSpeed() const {return m_Speed;}
	//Ϊ���ٱ��������ٶȵĺ���
	void addSpeed(float offerSpeed) { m_Speed += offerSpeed; }

private:


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


#endif
