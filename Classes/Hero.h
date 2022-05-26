#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"
#include "Entity.h"
#include "MathUtils.h"
#include "Character.h"
#include "ProgressView.h"

using namespace cocos2d;

class Hero :public Entity
{
public:
	bool init() override;

	//Ӣ�۵Ľ�ɫ
	Character m_Character;

	//Ӣ�۵�����
	Sprite* m_Body;

	//Ӣ�۵ļ���
	Sprite* m_Skill;


	//Ӣ���Ƿ������ƶ�
	bool m_isMoving;

	//Ӣ�۴����ƶ�������д(�����Ҷ����ļ�)
	std::string m_Direction;
public:
	//�������ţ���ɫ��ʼ����
	void setAnimation(const float& Angle);

	//ֹͣ�������ţ���ɫ��ֹ
	void stopAnimation();

	//��ͨ����
	void NormalAttack(const float& Angle);

	//ֹͣ��ͨ����
	void stopNormalAttack();

	virtual void AttackSomething() override;

	virtual void BeAttacked(const int& Damage) override;

	virtual void Death() override;

};

#endif
