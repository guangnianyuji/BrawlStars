#include "Hero.h"

bool Hero::init()
{
	m_Body = Sprite::create(m_Character.m_Name + "/" + m_Character.m_Name + "f1.png");
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

