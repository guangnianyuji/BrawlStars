#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"
#include "Entity/Entity.h"
#include "Util/MathUtils.h"
#include "Character.h"
#include "Util/ProgressView.h"
#include "Weapon.h"
#include "Util/TimeCounter.h"
#include "Util/PathFinding.h"
#include "Util/NotifyUtil.h"

using namespace cocos2d;

class Hero :public Entity
{

public:
	bool init() override;


	//�������ţ���ɫ��ʼ����
	void beganToMove(const float& Angle,const float Speed,Point EndPosition);

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

	float getBlood() const { if (this == nullptr) return 0.0f; else return m_Blood->getRealTimeBlood(); }

	//Ϊ���ٱ��������ٶ�
	void addSpeed(float offerSpeed) { m_Speed += offerSpeed; }

	//�õ��չ��������ӿ�
	float getNormalAttackDamage() const{ return m_NormalAttackDamage;} 

	//Ϊ���ٱ�������չ�
	void addNormalAttackDamage(float offerAttackDamage){ m_NormalAttackDamage+= offerAttackDamage; }

protected:

	//Ӣ�۵��ٶ�
	float m_Speed;

	//Ӣ���Ƿ������ƶ�
	bool m_isMoving;

	//Ӣ���չ��˺�
	float m_NormalAttackDamage;

	//Ӣ�۴����˺�
	float m_AceDamage;

	//Ӣ���Ƿ��Ѿ�����
	bool m_isDead = false;

	//Ӣ���Ƿ������˺�
	bool m_damageImmunity = false;

	//Ӣ�۴����ƶ�������д(�����Ҷ����ļ�)
	std::string m_Direction;


};


#endif
