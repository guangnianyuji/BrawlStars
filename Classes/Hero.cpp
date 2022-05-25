#include "Hero.h"

bool Hero::init()
{
	m_Body = Sprite::create(m_Character.m_Name + "/" + m_Character.m_Name + "f1.png");

	m_Skill = Sprite::create(m_Character.m_Name + "/" + "Skill/1.png");

	//m_Body->addChild(m_Skill);

	if (!Entity::init())
	{
		return false;
	}
	
	addChild(m_Body);

	m_isMoving = false;
	m_Direction = "a";//随意初始化无意义

	return true;
}

void Hero::setAnimation(const float& Angle)
{
	m_Skill->runAction(AnimationUtils::createSkillAnimation(m_Character.m_Name));

	std::string tempDirection;
	if (Angle > -3 * Pi / 4 && Angle < -Pi / 4)
	{
		tempDirection = "f";
	}
	else if (Angle < 3 * Pi / 4 && Angle > Pi / 4)
	{
		tempDirection = "b";
	}
	else if (Angle > 3 * Pi / 4 || Angle < -3 * Pi / 4)
	{
		tempDirection = "l";
	}
	else if (Angle > - Pi / 4 && Angle < 3*Pi / 4)
	{
		tempDirection = "r";
	}
	if (tempDirection != m_Direction)
	{
		m_Direction = tempDirection;
		m_Body->stopAllActions();
		m_Body->runAction(AnimationUtils::createAnimation(m_Character.m_Name, m_Direction));
	}
	runAction(MoveBy::create(0.1f, MathUtils::getVectorialSpeed(Angle, m_Character.m_Speed / 200)));
	m_isMoving = true;
}

void Hero::stopAnimation()
{
	if (m_isMoving)
	{
       m_Body->stopAllActions();
	   m_isMoving = false;
	}
}

void Hero::NormalAttack(const float& Angle)
{
	m_Skill->runAction(AnimationUtils::createNormalAttackAnimation(m_Character.m_Name));

	m_Skill->runAction(MoveBy::create(0.1f, MathUtils::getVectorialSpeed(Angle, m_Character.m_Speed / 200)));
}

void Hero::stopNormalAttack()
{
	m_Skill->runAction(AnimationUtils::createSkillAnimation(m_Character.m_Name));
}

