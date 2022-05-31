#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"
#include "Entity.h"
#include "MathUtils.h"
#include "Character.h"
#include "ProgressView.h"
#include "Weapon.h"

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

	//�������ĳЩ����
	virtual void AttackSomething() override;

	//����������
	virtual void BeAttacked(const float& Damage) override;

	//����
	virtual void Death() override;

	inline bool isDead() { return m_isDead; }

	//Ӣ�۵Ľ�ɫ
	Character m_Character;


	//�õ��ٶȵĽӿ�
	float getSpeed();

private:

	//Ӣ�۵�����
	//Sprite* m_Body;

	//Ӣ�۵ļ���
	Sprite* m_Skill;

	//Ӣ�۵��ٶ�
	float m_Speed;

	//Ӣ���Ƿ������ƶ�
	bool m_isMoving;

	//Ӣ���Ƿ��Ѿ�����
	bool m_isDead = false;


	//Ӣ�۴����ƶ�������д(�����Ҷ����ļ�)
	std::string m_Direction;


};

#endif
