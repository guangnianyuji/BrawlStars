#include"Character.h"

bool Character::operator==(Character& aCharacter)
{
	return this->m_Name == aCharacter.m_Name;
}


Fei::Fei() : Character()
{
	m_Name = "F";
	m_Speed = 35.0f;
	m_BloodVolume = 728.0f;
	m_NormalAttackDamage = 25.0f;
	m_Range = 200;
	m_IntervalTime = 0.5f;
	m_Count = 20;
	m_Duration = 18.0f;
	m_ACEIntervalTime = 0.8f;
	m_AceDamage = 168.0f;
}
Yu::Yu() : Character()
{
	m_Name = "Y";
	m_Speed = 30.0f;
	m_BloodVolume = 756.0f;
	m_NormalAttackDamage = 64.4f;
	m_Range = 150;
	m_IntervalTime = 0.60f;
	m_Count = 18;
	m_Duration = 15.0f;
	m_ACEIntervalTime = 20.0f;
	m_AceDamage = 0.0f;
}
Jide::Jide() : Character()
{
	m_Name = "J";
	m_Speed = 42.0f;
	m_BloodVolume = 672.0f;
	m_NormalAttackDamage = 72.0f;
	m_Range = 500;
	m_IntervalTime = 0.3f;
	m_Count = 12;
	m_Duration = 20.0f;
	m_ACEIntervalTime = 10.0f;
	m_AceDamage = 0.0f;
}
Lin::Lin() : Character()
{
	m_Name = "L";
	m_Speed = 40.0f;
	m_BloodVolume = 840.0f;
	m_NormalAttackDamage = 50.0f;
	m_Range = 100;
	m_IntervalTime = 0.70f;
	m_Count = 10;
	m_Duration = 22.0f;
	m_ACEIntervalTime = 25.0f;
	m_AceDamage = 0.0f;
}

Nothing::Nothing():Character()
{
	m_Name = "Nothing";
}