#include "Hero.h"

bool Hero::init()
{
	m_Body = m_Character.m_FrontBody;
	if (!Entity::init())
	{
		return false;
	}
	
	addChild(m_Body);

	m_isMoving = false;

	return true;
}

void Hero::setAnimation(const float& Angle)
{
	if (Angle > -3 * Pi / 4 &&  Angle < -Pi / 4)
	{
		m_Body = m_Character.m_FrontBody;
		m_Body->runAction(m_Character.m_FrontMove->clone ());
	}
	else if (Angle >  Pi / 4 && Angle < 3*Pi / 4)
	{
		m_Body = m_Character.m_BehindBody;
		m_Body->runAction(m_Character.m_BehindMove->clone());
	}
	else if (Angle >= 3 * Pi / 4 || Angle <= -3*Pi / 4)
	{
		m_Body = m_Character.m_LeftBody;
		m_Body->runAction(m_Character.m_LeftMove->clone());
	}
	else if (Angle >= -  Pi / 4 && Angle <=  Pi / 4)
	{
		m_Body = m_Character.m_RightBody;
		m_Body->runAction(m_Character.m_RightMove->clone());
	}
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

void Hero::onEnter()
{
	Entity::onEnter();
}