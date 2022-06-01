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
	m_Dutration = 0;
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
	m_Dutration = 10.0f;
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
	m_Dutration = 6.0f;
}

Nothing::Nothing():Character()
{
	m_Name = "Nothing";
}