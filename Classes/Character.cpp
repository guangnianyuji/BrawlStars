#include"Character.h"

bool Character::operator==(Character& aCharacter)
{
	return this->m_Name == aCharacter.m_Name;
}


Fei::Fei() : Character()
{
	m_Name = "F";
	m_Speed = 720;
	m_BloodVolume = 200.0f;
	m_NormalAttackDamage = 20;
	m_Range = 200;
	m_IntervalTime = 0.5f;
	m_Count = 3;
	m_Dutration = 30.0f;
	m_ACEIntervalTime = 5.0f;
	m_AceDamage = 50.0f;
}
Yu::Yu() : Character()
{
	m_Name = "Y";
	m_Speed = 720;
	m_BloodVolume = 200.0f;
	m_NormalAttackDamage = 50;
	m_Range = 300;
	m_IntervalTime = 1.50f;
	m_Count = 3;
	m_Dutration = 18.0f;
	m_ACEIntervalTime = 20.0f;
	m_AceDamage = 50.0f;
}
Jide::Jide() : Character()
{
	m_Name = "J";
	m_Speed = 720;
	m_BloodVolume = 200.0f;
	m_NormalAttackDamage = 20;
	m_Range = 500;
	m_IntervalTime = 2.0f;
	m_Count = 3;
	m_Dutration = 30.0f;
	m_ACEIntervalTime = 30.0f;
	m_AceDamage = 50.0f;
}
Lin::Lin() : Character()
{
	m_Name = "L";
	m_Speed = 720;
	m_BloodVolume = 200.0f;
	m_NormalAttackDamage = 20;
	m_Range = 300;
	m_IntervalTime = 5.0f;
	m_Count = 3;
	m_Dutration = 30.0f;
	m_ACEIntervalTime = 5.0f;
	m_AceDamage = 50.0f;
}

Nothing::Nothing():Character()
{
	m_Name = "Nothing";
}